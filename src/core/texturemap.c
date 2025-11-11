#include "../../lib/core/texturemap.h"
#include <SDL3_image/SDL_image.h>
#include <stdlib.h>

void texturemap_init(TextureMap *map) { map->head = NULL; }

void texturemap_append(TextureMap *map, const char *key, SDL_Texture *texture) {
  TextureEntry* new_entry = malloc(sizeof(TextureEntry)); 
  new_entry->key = strdup(key);
  new_entry->texture = texture;
  new_entry->next = map->head; 
  map->head = new_entry;
}

SDL_Texture *texturemap_get(const TextureMap *map, const char *key) {
  TextureEntry *iterate;
  for (iterate = map->head; iterate != NULL; iterate = iterate->next) {
    if (strcmp(key, iterate->key) == 0) {
      return iterate->texture;
    }
  }
  return NULL;
}

void texturemap_cleanup(TextureMap *map) {
  TextureEntry *temp;
  while (map->head != NULL) {
    temp = map->head;
    map->head = map->head->next;
    free(temp->key);
    SDL_DestroyTexture(temp->texture);
    free(temp);
  }
}
