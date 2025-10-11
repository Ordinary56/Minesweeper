#define SDL_MAIN_USE_CALLBACKS

#include "../lib/core/core.h"
#include "../lib/gui/scene.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdlib.h>

#define UNUSED_PARAM(x) (void)(x)

static SDL_FPoint mouseCoord = {0};
static Scene *current_scene = &main_menu_scene;

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
  render_init(&state->renderContext);
  // TODO: Add render function to the render list here
  render_add_to_list(
      &state->renderContext,
      (RenderCallback){.func = game_draw_grid, .userdata = NULL});
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
  render_update(&state->renderContext);

  // 60 FPS
  SDL_Delay(16);
  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *state, SDL_AppResult result) {
  AppState *appstate = state;
  render_cleanup(&appstate->renderContext);
}
