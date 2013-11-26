// Game.cpp
#include "Game.h"
#include "StateMainMenu.h"
#include "StatePlay.h"
#include <ctime>

// pause function to pause for i seconds
void pause(int i) {
	std::clock_t now = std::clock();
	std::clock_t end;
	end = now + i * CLOCKS_PER_SEC;
	while (now < end )
		now = std::clock();
}

// We should be able to detect when errors occur with SDL if there are
// unrecoverable errors, then we need to print an error message and quit the program
// Note this is NOT a class member
void exitFatalError(char *message)
{
    std::cout << message << " " << SDL_GetError();
    SDL_Quit();
    exit(1);
}

// Static data member of class
int Game::instances = 0;

// Constructor method
Game::Game(void)
{
	// We should only have ONE instance of the game class
	// Any more than that, and something has gone wrong somewhere!
	instances++;
	if (instances > 1)
		exitFatalError("Attempt to create multiple game instances");
	setupRC();
}

// Destructor method
// Perform any required clean up here
Game::~Game()
{
	TTF_CloseFont(textFont);
    SDL_DestroyWindow(window);
	SDL_Quit();
}

// Set up rendering context
// Sets values for, and creates an OpenGL context for use with SDL
void Game::setupRC(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) // Initialize video
        exitFatalError("Unable to initialize SDL");

    // Request an OpenGL 2.1 context.
	// If you request a context not supported by your drivers, no OpenGL context will be created
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // double buffering on
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8); // 8 bit alpha buffering

	// Optional: Turn on x4 multisampling anti-aliasing (MSAA)
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
 
    // Create 800x600 window
    window = SDL_CreateWindow("SDL OpenGL Demo for GED",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
	if (!window) // Check window was created OK
        exitFatalError("Unable to create window");
 
    context = SDL_GL_CreateContext(window); // Create opengl context and attach to window
    SDL_GL_SetSwapInterval(1); // set swap buffers to sync with monitor's vertical refresh rate

	// set up TrueType / SDL_ttf
	if (TTF_Init()== -1)
		exitFatalError("TTF failed to initialise.");

	textFont = TTF_OpenFont("MavenPro-Regular.ttf", 24);
	if (textFont == NULL)
		exitFatalError("Failed to open font.");

//	return window;
}



// Initialise OpenGL values and game related values and variables
void Game::init(void)
{
	// create and initialise the different game states
	// in this case this will entail loading and preparing all assets
	// in a real game, asset loading is typically done if different stages
	// to avoid long delays when starting the game
	playState = new StatePlay();
	playState->init(*this); // 'this' is a pointer to the current object, the '*' dereferences the pointer
	pause(1);
	mainMenuState = new StateMainMenu();
	mainMenuState->init(*this);
	pause(1);
	//currentState = playState; // should start in main menu state, but I havent implemented it yet!
	currentState = mainMenuState;
	currentState->enter();

	glClearColor(0.0, 0.0, 0.0, 0.0); // set background colour

	std::srand( std::time(NULL) );
}



// This function contains the main game loop
void Game::run(void) 
{
	bool running = true; // set running to true
	SDL_Event sdlEvent; // variable to detect SDL events

	std::cout << "Progress: About to enter main loop" << std::endl;

	// unlike GLUT, SDL requires you to write your own event loop
	// This puts much more power in the hands of the programmer
	// This simple loop only responds to the window being closed.
	while (running)	// the event loop
	{
		while (SDL_PollEvent(&sdlEvent))
		{
			if (sdlEvent.type == SDL_QUIT)
				running = false;
			else
				currentState->handleSDLEvent(sdlEvent, *this);

		}
		//currentState->update(); // this is the place to put a call to the game update function
		currentState->draw(window);
	}

}

void Game::setState(GameState * newState)
{
	currentState->exit();
	currentState = newState;
	newState->enter();
}

GameState * Game::getState(void)
{
	return currentState;
}

GameState * Game::getPlayState(void)
{
	return playState;
}

GameState * Game::getMainMenuState(void)
{
	return mainMenuState;
}
