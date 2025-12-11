#pragma once

#include "../gui/render.h"
#include "debugmalloc.h"
#include "enums.h"
#include "game.h"
#include "texture_list.h"

#define SDL_COLOR_BLACK (SDL_Color){0, 0, 0, 255}
#define SDL_COLOR_WHITE (SDL_Color){255, 255, 255, 255}
#define SDL_COLOR_RED (SDL_Color){255, 0, 0, 255}
#define SDL_COLOR_GREEN (SDL_Color){0, 255, 0, 255}
#define SDL_COLOR_BLUE (SDL_Color){0, 0, 255, 255}

void load_assets(TextureList *list, SDL_Renderer *renderer);
void load_tile_nums(TextureList *list, RenderContext *renderer);
void save_game_state(GameContext *ctx, int time_left);
void load_game_state(GameContext *ctx, int time_left);
