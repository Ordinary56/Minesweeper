#pragma once
#include <SDL3/SDL_render.h>

typedef struct TextureMap {
  char **keys;
  SDL_Texture **values;
  size_t count;
  size_t capacity;
} TextureMap;

void texturemap_init(TextureMap *map, SDL_Renderer *renderer);

SDL_Texture *texturemap_get(const TextureMap *map, const char *key);

void texturemap_cleanup(TextureMap *map);
