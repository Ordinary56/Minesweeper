#pragma once

#include "../gui/render.h"
#include "../gui/scene.h"
#include "debugmalloc.h"
#include "game.h"
#include "texture_list.h"
#include "timer.h"

typedef struct AppState {
  GameContext gameContext;
  RenderContext renderContext;
  TextureList map;
  Scene *current_scene;
  bool is_running;
  SDL_Cursor *default_cursor;
  SDL_Cursor *pointer_cursor;
} AppState;

void App_set(AppState *context);
void App_quit(bool flag);

const AppState *App_get(void);
const GameContext *App_get_gamecontext(void);
const RenderContext *App_get_rendercontext(void);

AppState* App_get_mut(void);
GameContext* App_get_gamecontext_mut(void);
RenderContext* App_get_rendercontext_mut(void);

SDL_Cursor *App_get_pointer_cursor(void);
SDL_Cursor *App_get_default_cursor(void);
