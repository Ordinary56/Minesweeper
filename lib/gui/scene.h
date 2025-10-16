#pragma once
#include <SDL3/SDL_render.h>
#include "../core/texturemap.h"
typedef struct Scene {
  void (*init)(void *);
  void (*update)(void *);
  void (*draw)(SDL_Renderer *, void *);
  void (*cleanup)();

} Scene;


// change the current scene
void scene_change_to(void *app, Scene *newScene, void* data);

extern Scene main_menu_scene;
extern Scene game_scene;
