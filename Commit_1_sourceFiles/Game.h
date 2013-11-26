#ifndef GAME_MAIN
#define GAME_MAIN

#include <iostream>
#include <SDL_opengl.h>
#include <SDL.h>
#include <SDL_ttf.h>

// C stdlib and C time libraries for rand and time functions
#include <cstdlib>
#include <ctime>
// iostream for cin and cout
#include <iostream>
// stringstream and string
#include <sstream>
#include <string>

// States
// first of these is actually redundant, as it will be included as part of each of
// the following two lines
#include "GameState.h"
#include "label.h"

class Game {
public:
	// Constructor and destructor methods
	Game(void);
	~Game();
	// init and run are the only functions that need called from main
	void init(void);
	void run(void);
	// Having the font specified in Game is probably not the best way of doing this
	// but for the current demo purposes "it'll do"
	TTF_Font * getFont(void) { return textFont; }
	void setState(GameState * newState);
	GameState *getState(void);
	GameState *getPlayState(void);
	GameState *getMainMenuState(void);
private:
	// The game states:
	GameState * playState;
	GameState * mainMenuState;
	GameState * currentState;

	// setupRC will be called when game is created
	void setupRC(void);
	// The game loop will call update, draw and handle event methods provided by each state

	SDL_Window *window;
	// This needs changed... currently I refer to the Game object as the context for the different
	// states, so should use a specific (and diff) name to refer to the gl context
	// to avoid confusion
	SDL_GLContext context;

	static int instances;

	clock_t lastTime; // clock_t is an integer type
	clock_t currentTime; // use this to track time between frames

	TTF_Font * textFont;	// SDL type for True-Type font rendering
};

#endif