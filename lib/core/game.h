#pragma once

#include "enums.h"
#include <SDL3/SDL_render.h>

static const unsigned short CELL_SIZE = 32;

typedef struct Cell {
  // 0 -> empty cell, used for flood fill
  // 1 - 8 -> how many of it's neighbours are mines
  // -1 -> it's a mine
  int val;

  bool flagged;
  bool revealed;

} Cell;

typedef struct GameContext {
  Cell **grid;
  int row, col;
  int placed_mines;
  CURRENT_GAME_STATE current_state;
} GameContext;

void game_init_default(GameContext *context);

bool game_create_grid(GameContext *context, GRID_SIZES grid_size);

void game_place_mines(GameContext *context, int num);

void game_flood_fill(GameContext *context);

void game_update(GameContext *context, void *data);

void game_cleanup(GameContext *context);
