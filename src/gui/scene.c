#include "../../lib/gui/scene.h"
#include "../../lib/core/core.h"
void scene_change_to(void *app, Scene *newScene, void *data) {
  AppState *state = app;
  if (state->current_scene) {
    state->current_scene->cleanup();
  }
  newScene->init(data);
  state->current_scene = newScene;
}
