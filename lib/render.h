#pragma once
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

typedef struct RenderState {
  SDL_Window* window;
  SDL_Renderer* renderer;
  TTF_Font* font;
} RenderState;

bool render_init(RenderState* renderState);

// TODO: expand this function
void render_update(RenderState* renderState);
void render_cleanup(RenderState* renderState);
