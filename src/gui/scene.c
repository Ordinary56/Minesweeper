#include "../../lib/gui/scene.h"
#include "../../lib/core/core.h"



void scene_change_to(Scene *newScene, void *data) {
  AppState* app_ref = App_get_mut();
  SDL_Log("App is %p", app_ref);
  if (app_ref->current_scene != NULL) {
    app_ref->current_scene->cleanup();
  }
  SDL_Log("init location: %p", &newScene->init);
  newScene->init(data);
  SDL_Log("New scene init successfull");
  app_ref->current_scene = newScene;
}
