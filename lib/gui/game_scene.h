#pragma once
#include <SDL3/SDL_render.h>

void game_scene_init(void* data);
void game_scene_draw_gui(SDL_Renderer *renderer, void *data);
void game_scene_draw_grid(SDL_Renderer *renderer, void *data);
void game_scene_draw(SDL_Renderer* renderer, void* data);

void game_scene_cleanup();
