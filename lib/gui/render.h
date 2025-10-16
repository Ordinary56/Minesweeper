#pragma once

// Includes
#include "scene.h"
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

// Constants
static const char *WINDOW_TITLE = "MINESWEEPER";
static const int MAX_RENDER_CALLBACKS = 64;
static const int WIDTH = 600;
static const int HEIGHT = 800;



typedef struct RenderContext {
  SDL_Window *window;
  SDL_Renderer *renderer;
  TTF_Font *font;

} RenderContext;

// Functions
bool render_init(RenderContext *rc);
void render_draw(RenderContext *rc, Scene* scene);
void render_cleanup(RenderContext *rc);
