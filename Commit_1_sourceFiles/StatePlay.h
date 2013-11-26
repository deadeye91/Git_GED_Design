#ifndef STATE_PLAY
#define STATE_PLAY

#include "gameState.h"
#include "Label.h"
// C stdlib and C time libraries for rand and time functions
#include <cstdlib>
#include <ctime>

class StatePlay : public GameState
{
public:
	StatePlay(void);
	~StatePlay(void);
	void init(Game &context);
	void draw(SDL_Window * window);
	void handleSDLEvent(SDL_Event const &sdlEvent, Game &context);
	void enter();
	void exit();
private:
	
	int score;

	// Another *strong* candidate for creating a new class type
	// is character/agent, to encapsulate player and target data,
	// potentially to include an Agent::draw() function and
	// perhaps also generalise collision detection
	// This is left as a further exercise
	float xpos;
	float ypos;
	float xsize;
	float ysize;

	float targetXPos;
	float targetYPos;
	float targetXSize;
	float targetYSize;

	clock_t lastTime; // clock_t is an integer type
	clock_t currentTime; // use this to track time between frames

	Label * playerLabel;
	Label * targetLabel;

	TTF_Font * textFont;	// SDL type for True-Type font rendering
};

#endif