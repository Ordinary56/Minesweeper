#pragma once
#include <SDL3/SDL.h>
#include "game.h"
#include "timer.h"
#include "render.h"
typedef struct AppState {
  GameState gameState;
  RenderState renderState;
  Timer timer;
} AppState;
