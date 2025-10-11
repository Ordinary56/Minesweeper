#include "../lib/gui/render.h"

bool render_init(RenderContext *rs) {
  rs->window = SDL_CreateWindow(WINDOW_TITLE, WIDTH, HEIGHT, 0);
  if (!rs->window) {
    return false;
  }
  rs->renderer = SDL_CreateRenderer(rs->window, NULL);
  if (!rs->renderer) {
    return false;
  }

  if (!TTF_Init()) {
    return false;
  }

  rs->font =
      TTF_OpenFont("/usr/share/fonts/TTF/OpenSans-Bold.ttf", 32.0f);
  if (!rs->font) {
    return false;
  }

  rs->callback_count = 0;
  return true;
}

void render_add_to_list(RenderContext *rs, RenderCallback callback) {
  if(rs->callback_count  < MAX_RENDER_CALLBACKS) {
      rs->callbacks[rs->callback_count++] = callback;
  }
  else {
      SDL_Log("Warning: Render list is full\n");
    
  }

}

void render_update(RenderContext *rs) {
  SDL_RenderClear(rs->renderer);
  for (size_t i = 0; i < rs->callback_count; i++) {
    rs->callbacks[i].func(rs->renderer, rs->callbacks[i].userdata);
  }
  SDL_RenderPresent(rs->renderer);
}

void render_cleanup(RenderContext *rs) {
  if (rs->font) {
    TTF_CloseFont(rs->font);
    TTF_Quit();
  }

  if (rs->renderer) {
    SDL_DestroyRenderer(rs->renderer);
  }
  if (rs->window) {
    SDL_DestroyWindow(rs->window);
  }
}
