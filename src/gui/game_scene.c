#include "../../lib/gui/game_scene.h"
#include "../../lib/core/game.h"
#include "../../lib/gui/render.h"
#include "../../lib/gui/scene.h"
#include <SDL3_image/SDL_image.h>
#include <stdio.h>
static TextureMap *map_ref;
void game_scene_init(void *data) { map_ref = data; }

void game_scene_draw_gui(SDL_Renderer *renderer, void *data) {

  // TODO: finish implementing
}

static void game_scene_draw_cell(SDL_Renderer *renderer, Cell *cell, int r,
                                 int c) {
  SDL_Texture *texture;
  if (cell->flagged) {
    texture = texturemap_get(map_ref, "tile_hidden");
  } else {
    char filename[16];
    snprintf(filename, sizeof(filename), "tile_%d", cell->val);
    texturemap_get(map_ref, filename);
  }
  SDL_FRect dst = {.h = CELL_SIZE,
                   .x = (c * CELL_SIZE) + (WIDTH / 2.0f),
                   .w = CELL_SIZE,
                   .y = (r * CELL_SIZE) + (HEIGHT / 2.0f)};

  SDL_RenderTexture(renderer, texture, NULL, &dst);
}

void game_scene_draw_grid(SDL_Renderer *renderer, void *data) {
  GameContext *context = data;
  for (size_t r = 0; r < context->row; r++) {
    for (size_t c = 0; c < context->col; c++) {
      game_scene_draw_cell(renderer, &context->grid[r][c], r, c);
    }
  }
}

void game_draw(SDL_Renderer *renderer, void *data) {
  game_scene_draw_gui(renderer, data);
  game_scene_draw_grid(renderer, data);
}

Scene game_scene = {

    .init = game_scene_init,
    .update = NULL,
    .draw = game_scene_draw,
    .cleanup = game_scene_cleanup

};
