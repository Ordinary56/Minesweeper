
#include "../../lib/gui/ui_element.h"
#include "../../lib/core/core.h"
#include "../../lib/core/utils.h"
#include "../../lib/gui/render.h"
#include "../../lib/gui/scene.h"
#include "../../lib/gui/ui_states.h"
#include <stdlib.h>

#define BUTTON(label, color, data, on_click)                                   \
  button_create(label, color, data, on_click)

#define RECT(x, y, w, h)                                                       \
  (SDL_FRect) { x, y, w, h }

// Global refs
static TextureList *map_ref = NULL;
static SDL_FPoint *mouse_pos = NULL;

// in-file global state
static UIState ui_state;

static void button_clicked(UIButton *element) {
  if (element->on_click) {
    element->on_click(element->data);
  }
}

void main_menu_init(void *data) {
  map_ref = data;
  SDL_Log("Ui state is: %p", &ui_state);
  ui_state.buttons[0] =
      BUTTON("Beginner", SDL_COLOR_WHITE, &ui_state, button_set_grid_beginner);
  ui_state.buttons[1] = BUTTON("Intermediate", SDL_COLOR_WHITE, &ui_state,
                               button_set_grid_intermediate);
  ui_state.buttons[2] =
      BUTTON("Expert", SDL_COLOR_WHITE, &ui_state, button_set_grid_expert);
  ui_state.buttons[3] =
      BUTTON("15 Min", SDL_COLOR_WHITE, &ui_state, button_set_timer_15min);
  ui_state.buttons[4] =
      BUTTON("25 Min", SDL_COLOR_WHITE, &ui_state, button_set_timer_25min);
  ui_state.buttons[5] =
      BUTTON("25 Min", SDL_COLOR_WHITE, &ui_state, button_set_timer_30min);
  ui_state.buttons[6] = BUTTON("Start", SDL_COLOR_WHITE, &ui_state, button_play);
  ui_state.buttons[7] = BUTTON("Exit", SDL_COLOR_WHITE, NULL, button_exit);

  SDL_Log("Buttons fully initialized, size: %ld", sizeof(ui_state.buttons)/sizeof(ui_state.buttons[0]));
  for (size_t i = 0; i < MAX_BUTTONS; i++) {
    button_set_pos(&ui_state.buttons[i], 100.0f, 100.0f * i, 150.0f, 150.0f);
  }
}

void main_menu_update(void *input) {
  mouse_pos = input;
  SDL_MouseButtonFlags flags = SDL_GetMouseState(&mouse_pos->x, &mouse_pos->y);
  for (size_t i = 0; i < MAX_BUTTONS; i++) {
    if (SDL_PointInRectFloat(mouse_pos, &ui_state.buttons[i].rect)) {
      SDL_SetCursor(App_get_pointer_cursor());
      if (flags & SDL_BUTTON_LMASK) {
        SDL_Log("Clicked button: %ld", i);
        button_clicked(&ui_state.buttons[i]);
      }
    } else {
      SDL_SetCursor(App_get_default_cursor());
    }
  }
}

void main_menu_draw(const RenderContext *rc, void *data) {
  for (size_t i = 0; i < MAX_BUTTONS; i++) {
    SDL_Texture *texture = texture_list_get(map_ref, ui_state.buttons[i].label);
    char *text = ui_state.buttons[i].label;
    // if this text hasn't been added to the texture_list
    if (texture == NULL) {
      texture_list_append_text(map_ref, rc->renderer, rc->font,
                               ui_state.buttons[i]);
      continue;
    }
    SDL_RenderTexture(rc->renderer, texture, NULL, &ui_state.buttons[i].rect);
  }
}

void main_menu_cleanup() {
  map_ref = NULL;
  mouse_pos = NULL;
  for (size_t i = 0; i < MAX_BUTTONS; i++) {
    free(ui_state.buttons[i].label);
  }
}

Scene main_menu_scene = {.init = main_menu_init,
                         .update = main_menu_update,
                         .draw = main_menu_draw,
                         .cleanup = main_menu_cleanup};
