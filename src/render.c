#include "../lib/render.h"

bool render_init(RenderState *renderState) {
  renderState->window = SDL_CreateWindow("TITLE", 600, 800, 0);
  if (!renderState->window) {
    return false;
  }
  renderState->renderer = SDL_CreateRenderer(renderState->window, NULL);
  if (renderState->renderer) {
    return false;
  }
  return true;
}

void render_cleanup(RenderState *renderState) {
  if (renderState->renderer) {
    SDL_DestroyRenderer(renderState->renderer);
  }
  if (renderState->window) {
    SDL_DestroyWindow(renderState->window);
  }
}
