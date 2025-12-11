#include "../../lib/core/utils.h"
#include "../../lib/core/texture_list.h"
#include <SDL3_image/SDL_image.h>
#include <dirent.h>
#include <errno.h>
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


void save_game_state(GameContext *ctx, int timer_left) {
  SDL_Log("Writing save file in state.bin");
  FILE *file = fopen("state.bin", "wb");
  if (file == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to open game state file: %s",
                 strerror(errno));
    return;
  }
  fwrite(&ctx->row, sizeof(int), 1, file);
  fwrite(&ctx->col, sizeof(int), 1, file);
  fwrite(&ctx->placed_mines, sizeof(int), 1, file);
  for (int i = 0; i < ctx->row; i++) {
    fwrite(ctx->grid[i], sizeof(Cell), ctx->col, file);
  }
  fwrite(&timer_left, sizeof(int), 1, file);
  fclose(file);
}

void load_game_state(GameContext *ctx, int time_left) {
  SDL_Log("Reading save file in state.bin");
  FILE *file = fopen("state.bin", "rb");

  if (file == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to open game state file: %s",
                 strerror(errno));
    return;
  }
  fread(&ctx->row, sizeof(int), 1, file);
  SDL_Log("Loaded row: %d", ctx->row);
  fread(&ctx->col, sizeof(int), 1, file);
  SDL_Log("Loaded col: %d", ctx->col);
  ctx->grid = malloc(ctx->row * sizeof(Cell*));
  for(int i = 0; i < ctx->row; i++) {
    ctx->grid[i] = malloc(ctx->col * sizeof(Cell));
  }
  fread(&ctx->placed_mines, sizeof(int), 1, file);
  SDL_Log("Loaded mines: %d", ctx->placed_mines);
  for (int i = 0; i < ctx->row; i++) {
    fread(ctx->grid[i], sizeof(Cell), ctx->col, file);
  }
  fclose(file);
}
