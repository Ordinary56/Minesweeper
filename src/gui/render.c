#include "../../lib/gui/render.h"

bool render_init(RenderContext *rc) {
  rc->window = SDL_CreateWindow(WINDOW_TITLE, WIDTH, HEIGHT, 0);
  if (!rc->window) {
    return false;
  }
  rc->renderer = SDL_CreateRenderer(rc->window, NULL);
  if (!rc->renderer) {
    return false;
  }

  if (!TTF_Init()) {
    return false;
  }

  rc->font = TTF_OpenFont("/usr/share/fonts/TTF/OpenSans-Bold.ttf", 32.0f);
  if (!rc->font) {
    return false;
  }

  return true;
}


void render_draw(RenderContext *rc, Scene* scene) {
  SDL_RenderClear(rc->renderer);
  scene->draw(rc->renderer, NULL);
  SDL_RenderPresent(rc->renderer);
}

void render_cleanup(RenderContext *rc) {
  if (rc->font) {
    TTF_CloseFont(rc->font);
    TTF_Quit();
  }

  if (rc->renderer) {
    SDL_DestroyRenderer(rc->renderer);
  }
  if (rc->window) {
    SDL_DestroyWindow(rc->window);
  }
}
