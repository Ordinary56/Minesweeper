#pragma once

#include <SDL3/SDL_render.h>


static const size_t CELL_SIZE = 32;

enum CURRENT_GAME_STATE {
  STOPPED = 0,
  PLAYING,
  WIN,
  LOSE
};

typedef struct Cell {
  // 0 -> empty cell, used for flood fill
  // 1 - 8 -> how many of it's neighbours are mines
  // -1 -> it's a mine
  int val;

  bool flagged;

} Cell;

typedef struct GameContext {
  Cell **grid;
  int row, col;
  int placed_mines;
  enum CURRENT_GAME_STATE current_state;
} GameContext;

void game_init_default(GameContext *context);

bool game_create_grid(GameContext *context);

void game_place_mines(GameContext *context, int num);

void game_flood_fill(GameContext* context);

void game_update(GameContext *context, void* data);

void game_draw_grid(SDL_Renderer* renderer, void* userdata);

void game_cleanup(GameContext *context);
