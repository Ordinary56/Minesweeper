#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "../lib/core/core.h"
#include "../lib/core/utils.h"
#include "../lib/gui/scene.h"
#include <stdlib.h>

#define UNUSED_PARAM(x) (void)(x)

static SDL_FPoint mouseCoord = {0};

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
  // Unused parameters
  UNUSED_PARAM(argc);
  UNUSED_PARAM(argv);

  // Appstate allocation
  *appstate = malloc(sizeof(AppState));
  if (!(*appstate)) {
    SDL_Log("[ main.c ] Failed to init AppState: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  SDL_Log("AppState initialized");

  AppState *state = *appstate;

  state->is_running = true;
  state->default_cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
  state->pointer_cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_POINTER);

  App_set(state);

  // Rendering
  if (!render_init(&state->renderContext)) {
    SDL_Log("[ main.c ] Failed to init RenderContext: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  SDL_Log("RenderContext initialized");

  // Texture and assets
  texture_list_init(&state->map);

  SDL_Log("TextureList initialized");
  load_assets(&state->map, state->renderContext.renderer);
  load_tile_nums(&state->map, &state->renderContext);

  SDL_Log("changing scene");
  SDL_Log("Scene's pointer is: %p", &main_menu_scene);
  // Scene 
  state->current_scene = NULL;
  scene_change_to(&main_menu_scene, &state->map);
  game_init_default(&state->gameContext);
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *e) {
  UNUSED_PARAM(appstate);
  switch (e->type) {
  case SDL_EVENT_QUIT:
    return SDL_APP_SUCCESS;
  case SDL_EVENT_MOUSE_MOTION:
      mouseCoord.x = e->motion.x;
      mouseCoord.y = e->motion.y;
    break;
  default:
    break;
  }
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  AppState *state = appstate;
  if(!state->is_running) {
    return SDL_APP_SUCCESS;
  }
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
  UNUSED_PARAM(result);
  AppState *appstate = state;
  game_cleanup(&appstate->gameContext);
  appstate->current_scene->cleanup();
  texture_list_cleanup(&appstate->map);
  render_cleanup(&appstate->renderContext);
  free(appstate);
  App_set(NULL);
}
