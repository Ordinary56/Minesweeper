#include "../../lib/core/enums.h"
#include "../../lib/gui/render.h"
#include "../../lib/gui/scene.h"
#include "../../lib/gui/ui_element.h"
#define MAX_BUTTONS 8 // 3 - grid size 3 - timer  2- start and exit button

// Global refs
static TextureMap *map_ref = NULL;



// UI state
typedef struct UIState {

  GRID_SIZES selected_grid_size;
  TIMERS selected_timer;
  UIButton buttons[MAX_BUTTONS];

} UIState;

// in-file global state
static UIState ui_state;

static void button_clicked(Uint8 id, UIButton *element) {
  GRID_SIZES size;
  TIMERS timer;
  void *data = element->data;
  switch (id) {
  case BUTTON_ID_START:
    break;
  case BUTTON_ID_GRID_SIZE:
    ui_state.selected_grid_size = *(GRID_SIZES *)data;
    break;
  case BUTTON_ID_TIMER:
    ui_state.selected_timer = *(TIMERS *)data;
    break;
  }
}

void main_menu_init(void *data) {
  map_ref = data;
  SDL_Color black_text = {.r = 0, .g = 0, .b = 0, .a = 255};
  // Unrolled konstansok miatt
  ui_state.buttons[0] =
      button_create("Beginner", black_text, (GRID_SIZES *)BEGINNER);
  ui_state.buttons[1] =
      button_create("Intermediate", black_text, (GRID_SIZES *)INTERMEDIATE);
  ui_state.buttons[1] =
      button_create("Expert", black_text, (GRID_SIZES *)EXPERT);
  ui_state.buttons[2] = button_create("Start", black_text, NULL);
  ui_state.buttons[3] = button_create("Exit", black_text, NULL);
}

void main_menu_update(void *input) {
  SDL_FPoint *mouse_coord = input;

  for (size_t i = 0; i < MAX_BUTTONS; i++) {
    if (SDL_PointInRectFloat(mouse_coord, &ui_state.buttons[i].rect)) {
      button_clicked(ui_state.buttons[i].id, &ui_state.buttons[i]);
    }
  }
}

void main_menu_draw(const RenderContext *rc, void *data) {
  for (size_t i = 0; i < MAX_BUTTONS; i++) {
    // TODO:  render text, render buttons
    SDL_Texture *texture = texturemap_get(map_ref, ui_state.buttons[i].label);
    char *text = ui_state.buttons[i].label;
    if (texture == NULL) {
      SDL_Surface *surface = TTF_RenderText_Solid(rc->font, text, strlen(text),
                                                  ui_state.buttons[i].color);
      texture = SDL_CreateTextureFromSurface(rc->renderer, surface);
      if (texture != NULL) {
        texturemap_append(map_ref, text, texture);
      }
      texture->h = ui_state.buttons[i].rect.h;
      texture->w = ui_state.buttons[i].rect.w;
    }
    SDL_RenderTexture(rc->renderer, texture, NULL, &ui_state.buttons[i].rect);
  }
}

void main_menu_cleanup() { map_ref = NULL; }

Scene main_menu_scene = {.init = main_menu_init,
                         .update = main_menu_update,
                         .draw = main_menu_draw,
                         .cleanup = main_menu_cleanup};
