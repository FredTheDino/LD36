#include "pie.h"

#include <SDL2/SDL.h>
#include "loader.h"

#include "gamestate.h"
#include "gamestatelibrary.h"
#include "root.h"
#include "entity.h"
#include "node.h"
#include "component.h"
#include "audiohandler.h"

#include "teststate.h"
#include "testcomponent.h"

int main(int c, char** args) {
	Jam::GameStateLibrary::registerGameState("TestState", (Jam::GameState*) new TestState());

	/*
	Jam::InputHandler::registerInput("t_increment", Jam::InputBinding(true, -1, 0, SDLK_o));
	Jam::InputHandler::registerInput("t_decrement", Jam::InputBinding(true, -1, 0, SDLK_i));
	Jam::InputHandler::registerInput("t_reset", Jam::InputBinding(true, -1, 0, SDLK_p));
	*/
	Jam::InputHandler::registerInput("t_play", Jam::InputBinding(true, -1, 0, SDLK_BACKSPACE));
	Jam::Time::setFPS(0);

	//Jam::Loader::prefix = "../res/";
	Jam::Loader::prefix = "../../res/";

	std::cout << Jam::Loader::loadText("test.txt") << std::endl;
	
	Jam::Flavor flavor;
	
	flavor.title = "My Test Game";
	flavor.enterState = "TestState";
	flavor.transparancy = true;

	Jam::Pie pie(flavor);

	pie.bake();

	return 0;
}