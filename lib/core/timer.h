#pragma once
#include <SDL3/SDL_timer.h>

#define MIN_TO_SEC(x) (x / 60)
#define SEC_TO_MIN(x) (x * 60)

typedef struct Timer {
  Uint32 countdown;
  Uint32 last_time;
} Timer;

void timer_init(Timer* timer);
void timer_tick(Timer* timer);

