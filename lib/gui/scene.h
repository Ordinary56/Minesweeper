#pragma once
#include "render.h"
#include "../core/texturemap.h"
#include <SDL3/SDL_render.h>
typedef struct Scene {
  void (*init)(void *);
  void (*update)(void *);
  void (*draw)(const RenderContext *rc, void *);
  void (*cleanup)();

} Scene;

// change the current scene
void scene_change_to(void *app, Scene *newScene, void *data);

extern Scene main_menu_scene;
extern Scene game_scene;
