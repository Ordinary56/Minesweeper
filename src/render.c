#include "../lib/render.h"

bool render_init(RenderState *renderState) {
  renderState->window = SDL_CreateWindow("TITLE", 600, 800, 0);
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
      TTF_OpenFont("/usr/share/fonts/TTF/OpenSans-Bold.ttf", 32);
  if (!renderState->font) {
  }
  return true;
}

void render_update(RenderState *renderState) {
  SDL_RenderClear(renderState->renderer);
  SDL_Texture *texture = NULL;
  SDL_Surface *text =
      TTF_RenderText_Blended(renderState->font, "Hello World!", 0,
                             (SDL_Color){255, 255, 255, SDL_ALPHA_OPAQUE});
  if (text) {
    texture = SDL_CreateTextureFromSurface(renderState->renderer, text);
  } else {
    SDL_Log("Failed to create text from surface: %s", SDL_GetError());
  }
  SDL_DestroySurface(text);
  SDL_RenderTexture(renderState->renderer, texture, NULL,
                    &(SDL_FRect){.h = 400, .w = 800, .x = 100, .y = 100});
  SDL_RenderPresent(renderState->renderer);
}

void render_cleanup(RenderState *renderState) {
  if (renderState->renderer) {
    SDL_DestroyRenderer(renderState->renderer);
  }
  if (renderState->window) {
    SDL_DestroyWindow(renderState->window);
  }

  if (renderState->font) {
    TTF_CloseFont(renderState->font);
    TTF_Quit();
  }
}
