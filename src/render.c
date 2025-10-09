#include "../lib/gui/render.h"

bool render_init(RenderState *renderState) {
  renderState->window = SDL_CreateWindow(WINDOW_TITLE, WIDTH, HEIGHT, 0);
  if (!renderState->window) {
    return false;
  }
  renderState->renderer = SDL_CreateRenderer(renderState->window, NULL);
  if (!renderState->renderer) {
    return false;
  }

  if (!TTF_Init()) {
    return false;
  }

  renderState->font =
      TTF_OpenFont("/usr/share/fonts/TTF/OpenSans-Bold.ttf", 32.0f);
  if (!renderState->font) {
    return false;
  }

  renderState->render_func_count = 0;
  return true;
}

void render_update(RenderState *renderState) {
  SDL_RenderClear(renderState->renderer);
  for (size_t i = 0; i < MAX_RENDER_FUNCTIONS; i++) {
    renderState->render_funcs[i](renderState->renderer);
  }
  SDL_RenderPresent(renderState->renderer);
}

void render_cleanup(RenderState *renderState) {
  if (renderState->font) {
    TTF_CloseFont(renderState->font);
    TTF_Quit();
  }

  if (renderState->renderer) {
    SDL_DestroyRenderer(renderState->renderer);
  }
  if (renderState->window) {
    SDL_DestroyWindow(renderState->window);
  }
}
