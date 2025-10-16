#pragma once
#include <SDL3/SDL_render.h>

typedef struct TextureMap {
  char **keys;
  SDL_Texture **values;
  size_t count;
} TextureMap;

void texturemap_init(TextureMap *map);

void texturemap_append(TextureMap* map, const char* key, SDL_Renderer* renderer);

SDL_Texture *texturemap_get(const TextureMap *map, const char *key);

void texturemap_cleanup(TextureMap* map);
