/* ----- Bank setup ----- */
#pragma bank=4
#include "StateIntroOutro.h"
UINT8 bank_STATE_INTRO = 4;
UINT8 bank_STATE_OUTRO = 4;


/* ----- Includes ----- */
#include "Keys.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "../res/src/intro1Map.h"
#include "../res/src/intro2Map.h"
#include "../res/src/intro3Map.h"
#include "../res/src/intro1Tiles.h"
#include "../res/src/intro2Tiles.h"
#include "../res/src/intro3Tiles.h"


/* ----- Defines ----- */
#define MAX_SCREENS  3

/* Tileset parameters
 * 1. always zero
 * 2. number of tiles in that tileset
 * 3. the tileset lable XYZ (extern unsigned char XYZ[]), see tileset .h file
 * 4. tileset bank N, see "bN"-part in filename xyzTiles.bN.c
 */
#define INTRO_TILES_PARAMS_1   0, 120, tutorialTiles, 4
#define INTRO_TILES_PARAMS_2   0, 120, tutorialTiles, 4
#define INTRO_TILES_PARAMS_3   0, 120, tutorialTiles, 4

#define OUTRO_TILES_PARAMS_1   0, 120, tutorialTiles, 4
#define OUTRO_TILES_PARAMS_2   0, 120, tutorialTiles, 4
#define OUTRO_TILES_PARAMS_3   0, 120, tutorialTiles, 4

/* Map parameters
 * 1. map width, use #define from map .h file
 * 2. map height, use #define from map .h file
 * 3. map label XYZ (extern unsigned char XYZ[]), see map .h file
 * 4. always zero
 * 5. always zero
 * 6. map bank N, see "bN"-part in filename xyzMap.bN.c
 */
#define INTRO_MAP_PARAMS_1     menuMapWidth, menuMapHeight, menuMap, 0, 0, 4
#define INTRO_MAP_PARAMS_2     menuMapWidth, menuMapHeight, menuMap, 0, 0, 4
#define INTRO_MAP_PARAMS_3     menuMapWidth, menuMapHeight, menuMap, 0, 0, 4

#define OUTRO_MAP_PARAMS_1     menuMapWidth, menuMapHeight, menuMap, 0, 0, 4
#define OUTRO_MAP_PARAMS_2     menuMapWidth, menuMapHeight, menuMap, 0, 0, 4
#define OUTRO_MAP_PARAMS_3     menuMapWidth, menuMapHeight, menuMap, 0, 0, 4


/* ----- Types / Enums ----- */
typedef enum {
	IS_INTRO,
	IS_OUTRO
} IntroOrOutro;

/* ----- Prototypes ----- */
static void StateIntroOutro_HandleInput(void);
static void StateIntroOutro_LoadScreen(void);
static void StateIntroOutro_NextState(void);


/* ----- Variables ----- */
static IntroOrOutro selection;
static UINT8 screen = 0;


/* ----- Functions ----- */

void Start_STATE_INTRO(void) {
	/* load intro settings */
	selection = IS_INTRO;
	screen = 0;
	StateIntroOutro_LoadScreen();

	BGP_REG = PAL_DEF(0, 1, 2, 3);
	SHOW_BKG;

	/* do not load music, menu music is still playing! */
}

void Update_STATE_INTRO(void) {
	StateIntroOutro_HandleInput();
}

void Start_STATE_OUTRO(void) {
	extern UINT8* victory_mod_Data[];

	/* load outro settings */
	selection = IS_OUTRO;
	screen = 0;
	StateIntroOutro_LoadScreen();

	BGP_REG = PAL_DEF(0, 1, 2, 3);
	SHOW_BKG;

	/* load victory music */
	PlayMusic(victory_mod_Data, 5, 1);
}

/**
 * \brief Handles the input for both intro and outro
 */
static void StateIntroOutro_HandleInput(void) {
	if (IntroOrOutro == IS_INTRO) {
		if (KEY_TICKED(J_START)) {
			/* skip intro, start the game */
			StateIntroOutro_NextState();
			return;
		}
	}

	/* next screen or start game */
	if (KEY_TICKED(J_A)) {
		/* increase number of current screen */
		screen++;

		if (screen != MAX_SCREENS) {
			/* load next screen */
			StateIntroOutro_LoadScreen();
		} else {
			/* the screen sequence is done, goto next state */
			StateIntroOutro_NextState();
		}
	}
}

/**
 * \brief Loads the given screens content
 */
static void StateIntroOutro_LoadScreen(void) {
	if (IntroOrOutro == IS_INTRO) {
		switch (screen) {
		case 0: {
			ZInitScrollTilesColor(INTRO_TILES_PARAMS_1, 0);
			InitScrollColor(INTRO_MAP_PARAMS_1, 0);
			break;
		}
		case 1: {
			ZInitScrollTilesColor(INTRO_TILES_PARAMS_2, 0);
			InitScrollColor(INTRO_MAP_PARAMS_2, 0);
			break;
		}
		case 2: {
			ZInitScrollTilesColor(INTRO_TILES_PARAMS_3, 0);
			InitScrollColor(INTRO_MAP_PARAMS_2, 0);
			break;
		}
		}
	} else {
		switch (screen) {
		case 0: {
			ZInitScrollTilesColor(OUTRO_TILES_PARAMS_1, 0);
			InitScrollColor(OUTRO_MAP_PARAMS_1, 0);
			break;
		}
		case 1: {
			ZInitScrollTilesColor(OUTRO_TILES_PARAMS_2, 0);
			InitScrollColor(OUTRO_MAP_PARAMS_2, 0);
			break;
		}
		case 2: {
			ZInitScrollTilesColor(OUTRO_TILES_PARAMS_3, 0);
			InitScrollColor(OUTRO_MAP_PARAMS_2, 0);
			break;
		}
		}
	}
}

/**
 * \brief Loads the next state, depending on intro or outro setting
 */
static void StateIntroOutro_NextState(void) {
	if (IntroOrOutro == IS_INTRO) {
		// load the game
		SetState(STATE_GAME, 1);
	} else {
		// load main menu
		SetState(STATE_MENU, 1);
	}
}