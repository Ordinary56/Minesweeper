#pragma once
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

typedef struct UIButton {
  Uint8 id;
  SDL_FRect rect;
  SDL_Color color;
  char* label;
  void* data;
} UIButton;

UIButton button_create(const char* label, SDL_Color color, void* data);


