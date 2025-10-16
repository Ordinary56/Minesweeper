#include "../../lib/gui/scene.h"

static TextureMap* map_ref;

void main_menu_init(void* data) {
  map_ref = data;
}

void main_menu_update(void* input) {

}

void main_menu_draw(SDL_Renderer* renderer, void* data) {

}

void main_menu_cleanup() {
  map_ref = NULL;
}

Scene main_menu_scene = {
  .init = main_menu_init,
  .update = main_menu_update,
  .draw = main_menu_draw,
  .cleanup = main_menu_cleanup
};
