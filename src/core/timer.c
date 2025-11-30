#include "../../lib/core/timer.h"
#include <SDL3/SDL.h>

static SDL_TimerID timer_id;
SDL_AtomicInt remaining;
Uint32 GameTimer(void *userdata, SDL_TimerID id, Uint32 interval) {
  if (SDL_GetAtomicInt(&remaining) > 0) {
    SDL_AddAtomicInt(&remaining, -1);
    return interval;
  } else {
    SDL_SetAtomicInt(&remaining, 0);
    return 0;
  }
}

void timer_init(TIMERS timer) {
  switch (timer) {
  case MIN_15:
    SDL_SetAtomicInt(&remaining, TO_MIN(15));
    break;
  case MIN_25:
    SDL_SetAtomicInt(&remaining, TO_MIN(25));
    break;
  case MIN_30:
    SDL_SetAtomicInt(&remaining, TO_MIN(30));
    break;
  }
  timer_id = SDL_AddTimer(1000, GameTimer, NULL);
}

int timer_get() { return SDL_GetAtomicInt(&remaining); }

void timer_destroy() { SDL_RemoveTimer(timer_id); }
