#ifndef ZGBMAIN_H
#define ZGBMAIN_H

#include "main.h"
#include "gb/hardware.h"
#include "palette.h"
#include "Print.h"
#include "Utils.h"
#include "Math.h"

#define MAX_TILE_ID 99

typedef enum {
	STATE_GAME,

	N_STATES
} STATE;

typedef enum {
	SPRITE_PLAYER,
	SPRITE_ENEMY,

	N_SPRITE_TYPES
} SPRITE_TYPE;

#endif