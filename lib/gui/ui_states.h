#pragma once

#include "../core/enums.h"
#include "ui_element.h"

#define MAX_BUTTONS 9 // 3 - grid size 3 - timer  2- start and exit button

// UI state
typedef struct UIState {

  GRID_SIZES selected_grid_size;
  TIMERS selected_timer;
  UIButton buttons[MAX_BUTTONS];

} UIState;

