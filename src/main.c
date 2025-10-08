#define SDL_MAIN_USE_CALLBACKS
#include "../lib/core.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdlib.h>

#define UNUSED_PARAM(x) (void)(x)

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
  UNUSED_PARAM(argc);
  UNUSED_PARAM(argv);
  *appstate = malloc(sizeof(AppState));
  if (!(*appstate)) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to init appstate: %s",
                 SDL_GetError());
    return SDL_APP_FAILURE;
  }

  AppState *state = *appstate;
  render_init(&state->renderState);
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *e) {
  UNUSED_PARAM(appstate);
  switch (e->type) {
  case SDL_EVENT_QUIT:
    return SDL_APP_SUCCESS;
  default:
    break;
  }
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  AppState *state = appstate;
  render_update(&state->renderState);
  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *state, SDL_AppResult result) {
  AppState *appstate = state;
  render_cleanup(&appstate->renderState);
}
