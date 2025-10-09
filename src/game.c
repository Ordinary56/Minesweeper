#include "../lib/core/game.h"
#include <SDL3/SDL_log.h>
#include <stdlib.h>
#include <time.h>

void game_init_default(GameState *gameState) {
  gameState->grid = NULL;
  gameState->row = 0, gameState->col = 0;
  gameState->placed_mines = 0;
  gameState->current_state = STOPPED;
  // TODO: init timer
}

bool game_init_grid(GameState *gameState) {

  gameState->grid = malloc(gameState->row * sizeof(Cell *));
  if (!gameState->grid)
    goto error;
  for (size_t i = 0; i < gameState->row; i++) {
    gameState->grid[i] = malloc(gameState->col * sizeof(Cell));
    if (!gameState->grid[i])
      goto error;
  }

  return true;

error:
  SDL_Log("Failed to initialize grid! System ran out of memory");
  return false;
}

void game_place_mines(GameState *gameState) {
  srand(time(NULL));
  int randX = rand() % gameState->row;
  int randY = rand() % gameState->col;

}

void game_update(GameState *gameState) {
  switch (gameState->current_state) {
  case STOPPED:
    return;
  case PLAYING:
    // TODO: handle input logic here
    break;
  case WIN:
  case LOSE:
    gameState->current_state = STOPPED;
    game_cleanup(gameState);
    game_init_default(gameState);
    break;
  }
}

void game_cleanup(GameState *gameState) {
  if (gameState->grid) {
    for (size_t i = 0; i < gameState->row; i++) {
      free(gameState->grid[i]);
    }
    free(gameState->grid);
    gameState->grid = NULL;
  }
}
