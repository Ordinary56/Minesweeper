#include "../../lib/core/texturemap.h"
#include <SDL3_image/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

static int CAPACITY = 25;

void texturemap_init(TextureMap *map) {
  map->count = 0;

  map->keys = malloc(CAPACITY * sizeof(char *));
  map->values = malloc(CAPACITY * sizeof(SDL_Texture *));
}

void texturemap_append(TextureMap *map, const char *key, SDL_Renderer *renderer) {

  if (texturemap_get(map, key) != NULL)
    return;
  map->count++;
  if (map->count > CAPACITY) {
    CAPACITY *= 2;
    map->keys = realloc(map->keys, CAPACITY);
    map->values = realloc(map->values, CAPACITY);
  }
  map->keys[map->count] = strdup(key);
  char filename[64];
  snprintf(filename, sizeof(filename), "../../assets/%s", key);
  SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
  map->values[map->count] = texture;
}

SDL_Texture *texturemap_get(const TextureMap *map, const char *key) {

  for (size_t i = 0; i < map->count; i++) {
    if (strcmp(map->keys[i], key) == 0) {
      return map->values[i];
    }
  }

  return NULL;
}

void texturemap_cleanup(TextureMap *map) {

  for (size_t i = 0; i < map->count; i++) {
    free(map->keys[i]);
    SDL_DestroyTexture(map->values[i]);
  }
  free(map->keys);
  free(map->values);

  map->count = 0;
  map->keys = NULL;
  map->values = NULL;
}
