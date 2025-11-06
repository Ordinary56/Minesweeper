#include "../../lib/core/game.h"
#include "../../lib/gui/render.h"
#include <SDL3/SDL_log.h>
#include <stdlib.h>
#include <time.h>

void game_init_default(GameContext *context) {
  context->grid = NULL;
  context->row = 0, context->col = 0;
  context->placed_mines = 0;
  context->current_state = STOPPED;
}

bool game_create_grid(GameContext *context, GRID_SIZES grid_size) {
  switch (grid_size) {
  case BEGINNER:
    context->row = 9;
    context->col = 9;
    break;
  case INTERMEDIATE:
    context->row = 16;
    context->col = 16;
    break;
  case EXPERT:
    context->row = 30;
    context->col = 16;
    break;
  }
  context->grid = malloc(context->row * sizeof(Cell *));
  if (!context->grid)
    goto error;
  for (size_t i = 0; i < context->row; i++) {
    context->grid[i] = malloc(context->col * sizeof(Cell));
    if (!context->grid[i])
      goto error;
    for (size_t j = 0; j < context->col; j++) {
      context->grid[i][j] =
          (Cell){.val = 0, .flagged = false, .revealed = false};
    }
  }

  return true;

error:
  SDL_Log("[game.c] : Failed to initialize grid! System ran out of memory!\n");
  return false;
}

int game_check_neighbours(GameContext *context, int row, int col) {
  int mine_count = 0;

  int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
  int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};

  for (size_t k = 0; k < 8; k++) {
    int nr = row + dr[k];
    int nc = col + dc[k];
    if (nr >= 0 && nr < context->row && nc >= 0 && nc < context->col) {
      if (context->grid[nr][nc].val == -1) {
        mine_count++;
      }
    }
  }
  return mine_count;
}

void game_place_mines(GameContext *context, int num) {
  srand(time(NULL));
  int randX = rand() % context->row;
  int randY = rand() % context->col;
  for (size_t i = 0; i < num; i++) {
    if (context->grid[randX][randY].val != -1) {
      context->grid[randX][randY] =
          (Cell){.flagged = false, .revealed = false, .val = -1};
      context->placed_mines++;
    }
  }
  // TODO:
  //  - set all cells to a num where it tells how many neighbours are mines

  for (size_t i = 0; i < context->row; i++) {
    for (size_t j = 0; j < context->col; j++) {
      Cell picked_cell = context->grid[i][j];
      picked_cell.val = game_check_neighbours(context, i, j);
    }
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
    if (local_x < 0 || local_y < 0 || local_x >= context->row ||
        local_y >= context->col) {
      return;
    }
    Cell picked_cell = context->grid[selected_row][selected_col];
    picked_cell.revealed = true;
    if (picked_cell.val == -1) {
      context->current_state = LOSE;
      break;
    }
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
