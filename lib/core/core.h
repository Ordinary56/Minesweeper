#pragma once
#include "game.h"
#include "timer.h"
#include "../gui/render.h"
typedef struct AppState {
  GameContext gameContext;
  RenderContext renderContext;
  Timer timer;
} AppState;

