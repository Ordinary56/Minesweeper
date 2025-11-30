#pragma once

#include "enums.h"
#include "debugmalloc.h"
#include "texture_list.h"
#include "../gui/render.h"

#define SDL_COLOR_BLACK (SDL_Color){0, 0, 0, 255}
#define SDL_COLOR_WHITE (SDL_Color){255, 255, 255, 255}
#define SDL_COLOR_RED (SDL_Color){255, 0, 0, 255}
#define SDL_COLOR_GREEN (SDL_Color){0, 255, 0, 255}
#define SDL_COLOR_BLUE (SDL_Color){0, 0, 255, 255}

void load_assets(TextureList *list, SDL_Renderer *renderer);

void load_tile_nums(TextureList* list, RenderContext* renderer);

void upload_high_score(const char* name, int time, GRID_SIZES size);
