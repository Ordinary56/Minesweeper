#include "../../lib/core/game.h"
#include "../../lib/core/debugmalloc.h"
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
  for (int i = 0; i < context->row; i++) {
    context->grid[i] = malloc(context->col * sizeof(Cell));
    if (!context->grid[i])
      goto error;
    for (int j = 0; j < context->col; j++) {
      context->grid[i][j] =
          (Cell){.val = 0, .flagged = false, .revealed = false};
    }
  }

  return true;

error:
  SDL_Log("[game.c] : Failed to initialize grid! System ran out of memory!\n");
  return false;
}

void game_set_state(GameContext *ctx, CURRENT_GAME_STATE state) {
  if (ctx->current_state != state) {
    ctx->current_state = state;
  }
}

bool game_cell_in_bounds(GameContext *ctx, int r, int c) {
  return (r >= 0 && r < ctx->row && c >= 0 && c < ctx->col);
}

int game_check_neighbours(GameContext *context, int row, int col) {
  int mine_count = 0;

  int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
  int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};

  for (int k = 0; k < 8; k++) {
    int nr = row + dr[k];
    int nc = col + dc[k];
    if (!game_cell_in_bounds(context, nr, nc)) {
      continue;
    }
    if (context->grid[nr][nc].val == -1) {
      mine_count++;
    }
  }
  return mine_count;
}

void game_place_mines(GameContext *context, int num) {
  srand(time(NULL));
  context->placed_mines = 0;

  while (context->placed_mines < num) {
    int randX = rand() % context->row;
    int randY = rand() % context->col;

    if (context->grid[randX][randY].val != -1) {
      SDL_Log("Placed mine at %d %d", randX, randY);
      context->grid[randX][randY] =
          (Cell){.flagged = false, .revealed = false, .val = -1};
      context->placed_mines++;
    }
  }

  for (int i = 0; i < context->row; i++) {
    for (int j = 0; j < context->col; j++) {
      if (context->grid[i][j].val != -1) {
        context->grid[i][j].val = game_check_neighbours(context, i, j);
      }
    }
  }
}

void game_flood_fill(GameContext *context, int r, int c) {

  if (!game_cell_in_bounds(context, r, c))
    return;

  Cell *cell = &context->grid[r][c];
  if (cell->flagged || cell->revealed) {
    return;
  }
  cell->revealed = true;
  if (cell->val != 0) {
    return;
  }

  for (int dr = -1; dr <= 1; dr++) {
    for (int dc = -1; dc <= 1; dc++) {
      if (dr == 0 && dc == 0)
        continue;
      int nr = r + dr;
      int nc = c + dc;

      if (game_cell_in_bounds(context, nr, nc)) {
        Cell *neighbor = &context->grid[nr][nc];
        if (!neighbor->revealed && !neighbor->flagged) {
          game_flood_fill(context, nr, nc);
        }
      }
    }
  }
}

void game_update(GameContext *context, void *data) {
  static bool left_prev = false;
  static bool right_prev = false;
  if (context->current_state == STOPPED) {
    return;
  }
  // if (timer_get() <= 0 && context->current_state != STOPPED) {
  //   timer_destroy();
  //   context->current_state = LOSE;
  // }
  SDL_FPoint *mouseCoords = data;
  SDL_MouseButtonFlags flags =
      SDL_GetMouseState(&mouseCoords->x, &mouseCoords->y);

  bool left_clicked = (flags & SDL_BUTTON_LMASK) && !left_prev;
  bool right_clicked = (flags & SDL_BUTTON_RMASK) && !right_prev;

  float grid_x = (WIDTH - (context->col * CELL_SIZE)) / 2.0f;
  float grid_y = (HEIGHT - (context->row * CELL_SIZE)) / 2.0f;

  float local_x = mouseCoords->x - grid_x;
  float local_y = mouseCoords->y - grid_y;

  int selected_row = (int)(local_y / CELL_SIZE);
  int selected_col = (int)(local_x / CELL_SIZE);

  if (!game_cell_in_bounds(context, selected_row, selected_col)) {
    return;
  }
  Cell *selected_cell = &context->grid[selected_row][selected_col];
  switch (context->current_state) {
  case STOPPED:
    return;
  case PLAYING:
    if (left_clicked) {
      if (selected_cell->val == -1) {
        context->current_state = LOSE;
      }
      game_flood_fill(context, selected_row, selected_col);
    } else if (right_clicked) {
      selected_cell->flagged = !selected_cell->flagged;
      SDL_Log("flagged %d", selected_cell->flagged);
    }
    break;
  case WIN:
  case LOSE:
    if (context->current_state != STOPPED) {
      context->current_state = STOPPED;
      game_cleanup(context);
      game_init_default(context);
    }
    break;
  }
  left_prev = left_clicked;
  right_prev = right_clicked;
}

void game_cleanup(GameContext *context) {
  if (context->grid) {
    for (int i = 0; i < context->row; i++) {
      free(context->grid[i]);
    }
    free(context->grid);
    context->grid = NULL;
  }
}
