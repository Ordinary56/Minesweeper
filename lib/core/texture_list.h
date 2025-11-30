#pragma once

#include "../../lib/core/debugmalloc.h"
#include <SDL3/SDL_render.h>
#include "../gui/ui_element.h"

typedef struct TextureEntry {
  char *key;
  SDL_Texture *texture;
  struct TextureEntry *next;
} TextureEntry;

typedef struct TextureList {
  TextureEntry *head;
} TextureList;

void texture_list_init(TextureList *list);
void texture_list_append(TextureList *list, const char *key, SDL_Texture *texture);
void texture_list_append_text(TextureList* list, SDL_Renderer* renderer, TTF_Font* font,UIButton button);
SDL_Texture *texture_list_get(const TextureList *list, const char *key);
void texture_list_cleanup(TextureList *list);
