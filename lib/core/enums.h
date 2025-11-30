#pragma once

typedef enum GRID_SIZES {
  // 9x9
  BEGINNER = 0,

  // 16x16
  INTERMEDIATE,

  // 30x16
  EXPERT
} GRID_SIZES;

typedef enum CURRENT_GAME_STATE {
  STOPPED = 0,
  PLAYING,
  WIN,
  LOSE
} CURRENT_GAME_STATE;

typedef enum TIMERS {
  MIN_15,
  MIN_25,
  MIN_30
} TIMERS;

