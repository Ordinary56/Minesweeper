#define SDL_MAIN_USE_CALLBACKS

#include "../lib/core/core.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdlib.h>

#define UNUSED_PARAM(x) (void)(x)

static SDL_FPoint mouseCoord = {0};

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
  UNUSED_PARAM(argc);
  UNUSED_PARAM(argv);
  *appstate = malloc(sizeof(AppState));
  if (!(*appstate)) {
    SDL_Log("[ main.c ] Failed to init appstate: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  AppState *state = *appstate;

  if (!render_init(&state->renderContext)) {
    SDL_Log("[ main.c ] Failed to init RenderContext: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  texturemap_init(&state->map, state->renderContext.renderer);
  state->current_scene = NULL;
  scene_change_to(state, &main_menu_scene, &state->map);
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *e) {
  UNUSED_PARAM(appstate);
  switch (e->type) {
  case SDL_EVENT_QUIT:
    return SDL_APP_SUCCESS;
  case SDL_EVENT_MOUSE_BUTTON_DOWN:
    if (e->button.button == 1) {
      mouseCoord.x = e->button.x;
      mouseCoord.y = e->button.y;
    }

    break;
  default:
    break;
  }
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  AppState *state = appstate;
  game_update(&state->gameContext, &mouseCoord);
  if (state->current_scene->update != NULL) {
    state->current_scene->update(&mouseCoord);
  }
  render_draw(&state->renderContext, state->current_scene);

  // 60 FPS
  SDL_Delay(16);
  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *state, SDL_AppResult result) {
  AppState *appstate = state;
  game_cleanup(&appstate->gameContext);
  appstate->current_scene->cleanup();
  texturemap_cleanup(&appstate->map);
  render_cleanup(&appstate->renderContext);
}
