#define _POSIX_C_SOURCE 200809L
#include <string.h>
#include "../../lib/core/texture_list.h"
#include "../../lib/core/debugmalloc.h"
#include <stdlib.h>
#include <SDL3_image/SDL_image.h>

#ifdef _WIN32
  #define strdup _strdup
#endif

void texture_list_init(TextureList *list) { list->head = NULL; }

void texture_list_append(TextureList *list, const char *key,
                         SDL_Texture *texture) {
  TextureEntry *new_entry = malloc(sizeof(TextureEntry));
  new_entry->key = strdup(key);
  new_entry->texture = texture;
  new_entry->next = list->head;
  list->head = new_entry;
}

void texture_list_append_text(TextureList *list, SDL_Renderer *renderer,
                              TTF_Font *font, UIButton button) {

  SDL_Surface *surface = TTF_RenderText_Solid(
      font, button.label, strlen(button.label), button.color);
  if (surface == NULL) {
    SDL_Log("[texture_list.c]: Error allocating memory for SDL_Surface at "
            "[texture_list_append_text]\n");
    return;
  }
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (texture == NULL) {
    SDL_Log("[texture_list.c]: Error allocating memory for SDL_Texture at "
            "[texture_list_append_text]\n");
    return;
  }
  SDL_DestroySurface(surface);
  surface = NULL;
  texture_list_append(list, button.label, texture);
}

SDL_Texture *texture_list_get(const TextureList *list, const char *key) {
  if (list == NULL || key == NULL) {
    return NULL;
  }
  TextureEntry *iterate;
  for (iterate = list->head; iterate != NULL; iterate = iterate->next) {
    if (strcmp(key, iterate->key) == 0) {
      return iterate->texture;
    }
  }
  return NULL;
}

void texture_list_cleanup(TextureList *list) {
  if (list == NULL) {
    return;
  }
  TextureEntry *temp;
  while (list->head != NULL) {
    temp = list->head;
    list->head = list->head->next;
    free(temp->key);
    SDL_DestroyTexture(temp->texture);
    free(temp);
  }
}
