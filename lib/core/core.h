#pragma once
#include "../gui/render.h"
#include "../gui/scene.h"
#include "game.h"
#include "texturemap.h"
#include "timer.h"


typedef struct AppState {
  GameContext gameContext;
  RenderContext renderContext;
  Timer timer;
  TextureMap map;
  Scene *current_scene;
} AppState;


