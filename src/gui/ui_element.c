#include "../../lib/gui/ui_element.h"
#include "../../lib/core/core.h"
#include "../../lib/core/utils.h"
#include "../../lib/core/texture_list.h"
#include "../../lib/gui/scene.h"
#include "../../lib/gui/ui_states.h"
#include <SDL3_ttf/SDL_ttf.h>

UIButton button_create(const char *label, SDL_Color color, void *data,
                       ButtonAction action) {
  UIButton button;
  button.label = strdup(label);
  button.color = color;
  button.data = data;
  button.on_click = action;
  return button;
}

void button_set_pos(UIButton *button, float x, float y, float w, float h) {
    button->rect.h = h;
    button->rect.w = w;
    button->rect.x = x;
    button->rect.y = y;
}

void button_set_grid_beginner(void *data) {
  UIState *state = data;
  state->selected_grid_size = BEGINNER;
  SDL_Log("Changed grid size to %d", state->selected_grid_size);
}

void button_set_grid_intermediate(void *data) {
  UIState *state = data;
  state->selected_grid_size = INTERMEDIATE;
  SDL_Log("Changed grid size to %d", state->selected_grid_size);
}
void button_set_grid_expert(void *data) {
  UIState *state = data;
  state->selected_grid_size = EXPERT;
  SDL_Log("Changed grid size to %d", state->selected_grid_size);
}

void button_set_timer_15min(void *data) {
  UIState *state = data;
  state->selected_timer = MIN_15;
}
void button_set_timer_25min(void *data) {
  UIState *state = data;
  state->selected_timer = MIN_25;
}
void button_set_timer_30min(void *data) {
  UIState *state = data;
  state->selected_timer = MIN_30;
}

void button_play(void *data) {
  UIState* state = data;
  scene_change_to(&game_scene, state);
}

void button_exit(void *data) {
  App_quit(false);
}

void button_save_state(void *data) {
  GameContext* game = data;
  int time_left = timer_get();
  save_game_state(game, time_left);
}

void button_load_game(void *data) {
  GameContext* game = data;
  int time_left = timer_get();
  load_game_state(game, time_left);
  scene_change_to(&game_scene, NULL);
}
