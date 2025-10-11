#include "../lib/core/game.h"
#include "../lib/gui/render.h"
#include <SDL3/SDL_log.h>
#include <stdlib.h>
#include <time.h>

void game_init_default(GameContext *context) {
  context->grid = NULL;
  context->row = 0, context->col = 0;
  context->placed_mines = 0;
  context->current_state = STOPPED;
  // TODO: init timer
}

bool game_create_grid(GameContext *context) {
  context->grid = malloc(context->row * sizeof(Cell *));
  if (!context->grid)
    goto error;
  for (size_t i = 0; i < context->row; i++) {
    context->grid[i] = malloc(context->col * sizeof(Cell));
    if (!context->grid[i])
      goto error;
  }

  return true;

error:
  SDL_Log("Failed to initialize grid! System ran out of memory!\n");
  return false;
}

void game_place_mines(GameContext *context, int num) {
  srand(time(NULL));
  int randX = rand() % context->row;
  int randY = rand() % context->col;
  for (size_t i = 0; i < num; i++) {
    context->grid[randX][randY] = (Cell){.flagged = false, .val = -1};
    context->placed_mines++;
  }
}



void game_update(GameContext *context, void *data) {

  SDL_FPoint *mouseCoords = data;
  float grid_x = (WIDTH - (context->col * CELL_SIZE)) / 2.0f;
  float grid_y = (HEIGHT - (context->row * CELL_SIZE)) / 2.0f;

  float local_x = mouseCoords->x - grid_x;
  float local_y = mouseCoords->y - grid_y;

  int selected_row = (int)(local_x / CELL_SIZE);
  int selected_col = (int)(local_y / CELL_SIZE);
  switch (context->current_state) {
  case STOPPED:
    return;
  case PLAYING:
    // TODO: handle input logic here
    if (local_x < 0 || local_y < 0 || local_x >= context->row ||
        local_y >= context->col) {
      return;
    }
    Cell picked_cell = context->grid[selected_row][selected_col];

    break;
  case WIN:
  case LOSE:
    context->current_state = STOPPED;
    game_cleanup(context);
    game_init_default(context);
    break;
  }
}

void game_cleanup(GameContext *context) {
  if (context->grid) {
    for (size_t i = 0; i < context->row; i++) {
      free(context->grid[i]);
    }
    free(context->grid);
    context->grid = NULL;
  }
}

void game_render(SDL_Renderer *renderer, void *data);
