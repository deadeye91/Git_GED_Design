#include "StatePlay.h"
#include <iostream>
// stringstream and string
#include <sstream>
#include <string>

// While a declaration of class Game has been provided in
// gamestate.h, this was only a forward declaration
// because we need to work with the implementation now
// we need to include game.h here
#include "Game.h"


StatePlay::StatePlay(void)
{
}


StatePlay::~StatePlay(void)
{
}

void StatePlay::init(Game &context)
{
	std::cout << "Initialising play state." << std::endl;

}

void StatePlay::enter()
{
	std::cout << "Entering play state. Press ESCAPE to return to menu" << std::endl;
}

void StatePlay::exit()
{
}

// The main rendering function
// In principle, this function should never perform updates to the game
// ONLY render the current state. Reacting to events should be taken care
// of in a seperate update function
void StatePlay::draw(SDL_Window * window)
{
	// Replace this with OpenGL draw calls to draw the main menu screen
	glClearColor(1.0f,0.0f,0.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	SDL_GL_SwapWindow(window); // swap buffers
}


// The event handling function
// In principle, this function should never perform updates to the game
// ONLY detect what events have taken place. Reacting to the events should
// be taken care of in a seperate update function
// This would allow e.g. diagonal movement when two keys are pressed together
// (which is not possible with this implementation)
void StatePlay::handleSDLEvent(SDL_Event const &sdlEvent, Game &context)
{
		std::cout << "Event handling in play state." << std::endl;
	if (sdlEvent.type == SDL_KEYDOWN)
	{
		//std::cout << "Scancode: " << sdlEvent.key.keysym.scancode ;
        //std::cout << ", Name: " << SDL_GetKeyName( sdlEvent.key.keysym.sym ) << std::endl;
		switch( sdlEvent.key.keysym.sym )
		{
			case SDLK_ESCAPE:
				context.setState(context.getMainMenuState());
			default:
				break;
		}
	}

}
