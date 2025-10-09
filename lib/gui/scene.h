
typedef struct Scene {
  void (*init)(void);
  void (*update)();
  void (*cleanup)();
} Scene;


void scene_manager_set_scene(Scene* newScene);
void scene_manager_update();



