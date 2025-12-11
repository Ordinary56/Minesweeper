#include "../../lib/core/core.h"
#include "../../lib/core/game.h"
#include "../../lib/core/utils.h"
#include "../../lib/gui/render.h"
#include "../../lib/gui/scene.h"
#include "../../lib/gui/ui_states.h"
#include <SDL3_image/SDL_image.h>
#include <stdio.h>

static UIButton save_button;

void game_scene_init(void *data) {
  UIState *state = data;

  save_button = button_create("Save Current game", SDL_COLOR_WHITE,
                              App_get_gamecontext_mut(), button_save_state);
  SDL_Log("Created save button");
  button_set_pos(&save_button, 350.0f, 550.0f, 200.0f, 200.0f);
  SDL_Log("Set save button pos");
  texture_list_append_text(&App_get_mut()->map,
                           App_get_rendercontext()->renderer,
                           App_get_rendercontext()->font, save_button);
  SDL_Log("Button text appeneded");
  game_set_state(App_get_gamecontext_mut(), PLAYING);
  if (state != NULL) {
    SDL_Log("State is not null, setting default inits for game");
    game_create_grid(App_get_gamecontext_mut(), state->selected_grid_size);
    game_place_mines(App_get_gamecontext_mut(), 10);
    timer_init(state->selected_timer);
  }
  SDL_Log("Game_Scene Init successful");
  for (int i = 0; i < App_get_gamecontext()->row; i++) {
    for (int j = 0; j < App_get_gamecontext()->col; j++) {
      Cell cell = App_get_gamecontext()->grid[i][j];
      SDL_Log("{.flagged = %d, .val = %d, .revealed = %d}", cell.flagged,
              cell.val, cell.revealed);
    }
    SDL_Log("\n");
  }
}

void game_scene_draw_gui(const RenderContext *ctx, void *data) {
  // static int last_seconds = -1;
  // static SDL_Texture *cached_tex = NULL;
  // static SDL_FRect dst = {.x = 15, .y = 15, .w = 300, .h = 100};
  // int seconds = INTERVAL_TO_SECONDS(timer_get());
  // if (seconds != last_seconds) {
  //   last_seconds = seconds;

  //   if (cached_tex)
  //     SDL_DestroyTexture(cached_tex);

  //   char str[64];
  //   snprintf(str, sizeof(str), "Time Remaining: %d s", seconds);

  //   SDL_Surface *surface =
  //       TTF_RenderText_Solid(ctx->font, str, strlen(str), SDL_COLOR_WHITE);

  //   cached_tex = SDL_CreateTextureFromSurface(ctx->renderer, surface);
  //   SDL_DestroySurface(surface);
  // }

  // if (cached_tex) {
  //   SDL_RenderTexture(ctx->renderer, cached_tex, NULL, &dst);
  // }
  // SDL_Log("%d", seconds);
  SDL_Texture *text = texture_list_get(&App_get()->map, save_button.label);
  SDL_RenderTexture(ctx->renderer, text, NULL, &save_button.rect);
}

static void game_scene_draw_cell(SDL_Renderer *renderer, Cell *cell, int r,
                                 int c) {
  SDL_Texture *texture;
  if (!cell->revealed) {
    if (cell->flagged) {
      texture = texture_list_get(&App_get()->map, "flag.png");
    } else {
      texture = texture_list_get(&App_get()->map, "tile_hidden_32x32.png");
    }
  } else {
    char tile_name[7];
    snprintf(tile_name, sizeof(tile_name), "tile_%d", cell->val);
    texture = texture_list_get(&App_get()->map, tile_name);
  }
  float grid_x = (WIDTH - (App_get_gamecontext()->col * CELL_SIZE)) / 2.0f;
  float grid_y = (HEIGHT - (App_get_gamecontext()->row * CELL_SIZE)) / 2.0f;
  SDL_FRect dst = {.h = CELL_SIZE,
                   .x = grid_x + (c * CELL_SIZE),
                   .w = CELL_SIZE,
                   .y = grid_y + (r * CELL_SIZE)};
  SDL_RenderTexture(renderer, texture, NULL, &dst);
}

void game_scene_draw_grid(SDL_Renderer *renderer, void *data) {
  const GameContext *context = App_get_gamecontext();
  for (size_t r = 0; r < context->row; r++) {
    for (size_t c = 0; c < context->col; c++) {
      game_scene_draw_cell(renderer, &context->grid[r][c], r, c);
    }
  }
}

void game_scene_draw(const RenderContext *rc, void *data) {
  game_scene_draw_gui(rc, data);
  game_scene_draw_grid(rc->renderer, data);
}

void game_scene_update(void *data) {
  SDL_FPoint *mouse_coord = data;
  SDL_MouseButtonFlags flags =
      SDL_GetMouseState(&mouse_coord->x, &mouse_coord->y);
  bool left_clicked = (flags & SDL_BUTTON_LMASK);
  if (SDL_PointInRectFloat(mouse_coord, &save_button.rect) && left_clicked) {
    save_button.on_click(save_button.data);
  }
}

void game_scene_cleanup() {
  timer_destroy();
  free(save_button.label);
}

Scene game_scene = {

    .init = game_scene_init,
    .update = game_scene_update,
    .draw = game_scene_draw,
    .cleanup = game_scene_cleanup

};
