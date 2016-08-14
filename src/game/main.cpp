#include "pie.h"

#include <SDL2/SDL.h>
#include "loader.h"

int main(int c, char** args) {

	Jam::InputHandler::registerInput("fpsDOWN", Jam::InputBinding(true, -1, 0, SDLK_1));
	Jam::InputHandler::registerInput("fpsUP", Jam::InputBinding(true, -1, 0, SDLK_2));

	Jam::Time::setFPS(60);

	//Jam::Loader::prefix = "../res/";
	Jam::Loader::prefix = "../../res/";

	std::cout << Jam::Loader::loadText("test.txt") << std::endl;
	
	Jam::Flavor flavor;
	
	flavor.title = "My Test Game";

	Jam::Pie pie(flavor);

	pie.bake();

	return 0;
}