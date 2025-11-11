#pragma once
#include <SDL3/SDL_render.h>

typedef struct TextureEntry {
  char *key;
  SDL_Texture *texture;
  struct TextureEntry *next;
} TextureEntry;

typedef struct TextureMap {
  TextureEntry *head;
} TextureMap;

void texturemap_init(TextureMap *map);
void texturemap_append(TextureMap *map, const char *key, SDL_Texture *texture);
SDL_Texture *texturemap_get(const TextureMap *map, const char *key);
void texturemap_cleanup(TextureMap *map);
