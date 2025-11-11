#include "../../lib/core/utils.h"
#include "../../lib/core/texturemap.h"
#include <SDL3_image/SDL_image.h>
#include <dirent.h>
#include <stdio.h>
#define FILEPATH_MAX 128

// Betölti az Assets mappában található összes képet
void load_assets(TextureMap *map, SDL_Renderer *renderer) {
  DIR *assets_folder = opendir("../../assets/");
  struct dirent *iterate;
  char file_path[FILEPATH_MAX];
  while ((iterate = readdir(assets_folder)) != NULL) {
    snprintf(file_path, FILEPATH_MAX, "../../assets/%s", iterate->d_name);
    SDL_Texture *texture = IMG_LoadTexture(renderer, file_path);
    texturemap_append(map, file_path, texture);
  }
  closedir(assets_folder);
}
