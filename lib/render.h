#pragma once
#include <SDL3/SDL_render.h>
typedef struct RenderState {
  SDL_Window* window;
  SDL_Renderer* renderer;
} RenderState;

bool render_init(RenderState* renderState);

// TODO: expand this function
void render_update(RenderState* renderState);
void render_cleanup(RenderState* renderState);
