#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>



SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv) {

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* e) {

  switch (e->type) {
    case SDL_EVENT_QUIT:
      return SDL_APP_SUCCESS;
    default:
      break;
  }
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {

  return SDL_APP_CONTINUE;
}


void SDL_AppQuit(void* state) {


}
