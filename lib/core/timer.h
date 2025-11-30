#pragma once
#include "enums.h"
#include <SDL3/SDL_atomic.h>
#include <SDL3/SDL_timer.h>

#define TO_MIN(x) (x * 60 * 1000)
#define INTERVAL_TO_SECONDS(x) (x / 1000)

typedef struct {
  int remaining;
} CountDownState;

void timer_init(TIMERS timer);

int timer_get();
void timer_destroy();
