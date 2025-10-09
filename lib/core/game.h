#pragma once
#include "timer.h"

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

typedef struct GameState {
  Cell **grid;
  int row, col;
  int placed_mines;
  enum CURRENT_GAME_STATE current_state;
} GameState;

// Initalizes the gamestate to it's default values
void game_init_default(GameState *gameState);

// Initializes the grid
bool game_init_grid(GameState *gameState);

// places mines on the grid
void game_place_mines(GameState *gameState);

void flood_fill();

// update logic, called every frame
void game_update(GameState *gameState);

// cleanup function. Used for freeing up the grid
void game_cleanup(GameState *gameState);
