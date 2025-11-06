#include "../../lib/core/texturemap.h"
#include <SDL3_image/SDL_image.h>
#if __gnu_linux__
#include <dirent.h>
#endif
#include <stdio.h>
#include <stdlib.h>

static int MAX_PATH = 256;

void texturemap_init(TextureMap *map, SDL_Renderer *renderer) {
  map->count = 0;
  map->capacity = 25;
  map->keys = malloc(map->capacity * sizeof(char *));
  map->values = malloc(map->capacity * sizeof(SDL_Texture *));

  DIR *assets_folder = opendir("../../assets/");
  struct dirent *iterate;
  char file_path[MAX_PATH];
  while ((iterate = readdir(assets_folder)) != NULL) {
    if (map->count >= map->capacity) {
      map->capacity *= 2;
      map->keys = realloc(map->keys, map->capacity * sizeof(char *));
      map->values = realloc(map->values, map->capacity * sizeof(SDL_Texture *));
    }
    snprintf(file_path, MAX_PATH, "../../assets/%s", iterate->d_name);
    map->keys[map->count] = strdup(iterate->d_name);
    map->values[map->count] = IMG_LoadTexture(renderer, file_path);
    map->count++;
  }
  closedir(assets_folder);
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
