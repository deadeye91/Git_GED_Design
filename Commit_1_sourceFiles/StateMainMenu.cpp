#include "StateMainMenu.h"
#include <iostream>

// While a declaration of class Game has been provided in
// gamestate.h, this was only a forward declaration
// because we need to work with the implementation now
// we need to include game.h here
#include "Game.h"


StateMainMenu::StateMainMenu(void)
{
}


StateMainMenu::~StateMainMenu(void)
{
}

void StateMainMenu::init(Game &context)
{
	std::cout << "Initialising main menu state" << std::endl;

}

void StateMainMenu::enter()
{
	std::cout << "Entering main menu state: Press RETURN to play or ESCAPE to quit " << std::endl;
}

void StateMainMenu::exit()
{
}


void StateMainMenu::draw(SDL_Window * window)
{
	glColor3f(1.0,1.0,1.0);
	TTF_Font *textFont = TTF_OpenFont("MavenPro-Regular.ttf", 24);
	std::stringstream strStream;
	strStream << "Main Menu" <<std::endl;
	Label :: displayString(-0.6,0.8, strStream.str().c_str(),textFont);
	SDL_GL_SwapWindow(window); // swap buffers
}

void StateMainMenu::handleSDLEvent(SDL_Event const &sdlEvent, Game &context)
{
	// Add additional input checks for any other actions carried out in this state
	std::cout << "Event handling in main menu state." << std::endl;
	if (sdlEvent.type == SDL_KEYDOWN)
	{
		//std::cout << "Scancode: " << sdlEvent.key.keysym.scancode ;
        //std::cout << ", Name: " << SDL_GetKeyName( sdlEvent.key.keysym.sym ) << std::endl;
		switch( sdlEvent.key.keysym.sym )
		{
			case SDLK_RETURN:
			case SDLK_RETURN2:
				context.setState(context.getPlayState());
				break;
			case SDLK_ESCAPE:
				// Create a SDL quit event and push into the event queue
				SDL_Event quitEvent;
				quitEvent.type = SDL_QUIT;
				SDL_PushEvent(&quitEvent);
			default:
				break;
		}
	}
}


