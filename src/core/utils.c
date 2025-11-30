#include "../../lib/core/utils.h"
#include "../../lib/core/texture_list.h"
#include <SDL3_image/SDL_image.h>
#include <dirent.h>
#include <stdio.h>
#define ENUM_TO_STR(a) #a
#define FILEPATH_MAX 128

// Betölti az Assets mappában található összes képet
void load_assets(TextureList *list, SDL_Renderer *renderer) {
  DIR *assets_folder = opendir("assets/");
  struct dirent *iterate;
  char file_path[FILEPATH_MAX];
  while ((iterate = readdir(assets_folder)) != NULL) {
    snprintf(file_path, FILEPATH_MAX, "assets/%s", iterate->d_name);
    SDL_Texture *texture = IMG_LoadTexture(renderer, file_path);
    if (texture == NULL) {
      SDL_Log("[utils.c/load_assets] Failed to load texture: %s reason: %s",
              file_path, SDL_GetError());
      continue;
    }
    SDL_Log("[utils.c/load_assets] Loading texture %s", file_path);
    texture_list_append(list, iterate->d_name, texture);
  }
  closedir(assets_folder);
}

void load_tile_nums(TextureList *list, RenderContext *ctx) {
  char tile[7];
  char num[2];
  for (int i = 0; i <= 8; i++) {
    snprintf(tile, sizeof(tile), "tile_%d", i);
    snprintf(num, sizeof(num), "%d", i);
    SDL_Log("%s", tile);
    SDL_Surface *surface =
        TTF_RenderText_Solid(ctx->font, num, sizeof(num), SDL_COLOR_WHITE);
    if (surface == NULL) {
      SDL_Log("[utils.c/load_tile_nums] failed to load surface for tile %d", i);
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(ctx->renderer, surface);
    if (texture == NULL) {

      SDL_Log("[utils.c/load_tile_nums] failed to load texture for tile %d", i);
    }

    SDL_DestroySurface(surface);
    texture_list_append(list, tile, texture);
  }
}

void upload_high_score(const char *name, int time, GRID_SIZES size) {
  FILE *file = fopen("highscore.txt", "a");
  if (file == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to open highscore");
    return;
  }
  char dest_str[64];
  snprintf(dest_str, sizeof(dest_str), "%s - TIME: %d s - DIFFICULTY: %s", name, time, ENUM_TO_STR(size));
  fprintf(file, dest_str);
  fclose(file);
}
