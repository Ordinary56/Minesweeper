#pragma once

#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

typedef void (*ButtonAction)(void* data);

typedef struct UIButton {
  SDL_FRect rect;
  SDL_Color color;
  char* label;
  void* data;
  ButtonAction on_click;
} UIButton;

UIButton button_create(const char* label, SDL_Color color, void* data, ButtonAction action);

void button_set_pos(UIButton* button, float x, float y, float w, float h);

void button_play(void* data);
void button_exit(void* data);


void button_load_game(void* data);
void button_save_state(void* data);

void button_set_grid_beginner(void* data);
void button_set_grid_intermediate(void* data);
void button_set_grid_expert(void* data);


void button_set_timer_15min(void* data);
void button_set_timer_25min(void* data);
void button_set_timer_30min(void* data);



