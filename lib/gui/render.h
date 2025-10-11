#pragma once

// Includes
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

// Constants
#define WINDOW_TITLE "MINESWEEPER"
#define MAX_RENDER_CALLBACKS 64
static const int WIDTH = 600;
static const int HEIGHT = 800;

typedef void (*RenderFunc)(SDL_Renderer* renderer, void* userdata);

typedef struct RenderCallback {
  RenderFunc func; 
  void* userdata;
} RenderCallback;

typedef struct RenderContext {
  SDL_Window *window;
  SDL_Renderer *renderer;
  TTF_Font *font;
  RenderCallback callbacks[MAX_RENDER_CALLBACKS];
  size_t callback_count;

} RenderContext;


// Functions
bool render_init(RenderContext *rs);
void render_add_to_list(RenderContext *rs, RenderCallback callback);
void render_update(RenderContext *rs);
void render_cleanup(RenderContext *rs);
