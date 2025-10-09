#pragma once

#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

#define WINDOW_TITLE "MINESWEEPER"
#define WIDTH 600
#define HEIGHT 800

#define MAX_RENDER_FUNCTIONS 64

typedef struct RenderState {
  SDL_Window *window;
  SDL_Renderer *renderer;
  TTF_Font *font;
  void (*render_funcs[MAX_RENDER_FUNCTIONS])(SDL_Renderer*);
  int render_func_count;

} RenderState;

bool render_init(RenderState *renderState);
void render_update(RenderState *renderState);
void render_cleanup(RenderState *renderState);
