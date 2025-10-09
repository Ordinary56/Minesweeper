#pragma once
#include "game.h"
#include "timer.h"
#include "../gui/render.h"
typedef struct AppState {
  GameState gameState;
  RenderState renderState;
  Timer timer;
} AppState;

