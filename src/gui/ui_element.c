#include "../../lib/gui/ui_element.h"
#include "../../lib/core/texturemap.h"
#include <SDL3_ttf/SDL_ttf.h>

static char *current_label = NULL;

UIButton button_create(const char *label, SDL_Color color, void *data) {
  UIButton button;
  button.label = strdup(label);
  button.data = data;

  return button;
}

