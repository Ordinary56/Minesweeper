#include "../../lib/core/core.h"

static AppState *app_ref = NULL;

void App_set(AppState *state) { app_ref = state; }

void App_quit(bool flag) { app_ref->is_running = flag; }

const AppState *App_get() { return app_ref; }

const GameContext *App_get_gamecontext() { return &app_ref->gameContext; }

const RenderContext *App_get_rendercontext() { return &app_ref->renderContext; }

AppState *App_get_mut(void) { return app_ref; }

GameContext *App_get_gamecontext_mut(void) { return &app_ref->gameContext; }

RenderContext *App_get_rendercontext_mut(void) {
  return &app_ref->renderContext;
}
SDL_Cursor *App_get_pointer_cursor() { return app_ref->pointer_cursor; }

SDL_Cursor *App_get_default_cursor() { return app_ref->default_cursor; }
