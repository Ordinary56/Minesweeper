#pragma once
#include <SDL3/SDL_render.h>

typedef struct Scene {
  void (*init)(void);
  void (*update)();
  void (*render)(SDL_Renderer*, void*);
  void (*cleanup)();
} Scene;


// change the current scene 
void scene_manager_set_scene(Scene* newScene);


extern Scene main_menu_scene;
