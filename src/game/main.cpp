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

void registerStuff();

int main(int c, char** args) {
	Jam::GameStateLibrary::registerGameState("test1", (Jam::GameState*) new TestState());

	/*
	Jam::InputHandler::registerInput("t_increment", Jam::InputBinding(true, -1, 0, SDLK_o));
	Jam::InputHandler::registerInput("t_decrement", Jam::InputBinding(true, -1, 0, SDLK_i));
	Jam::InputHandler::registerInput("t_reset", Jam::InputBinding(true, -1, 0, SDLK_p));
	*/
	Jam::InputHandler::registerInput("ui_select", Jam::InputBinding(1));
	Jam::InputHandler::registerInput("t_play", Jam::InputBinding(true, -1, 0, SDLK_BACKSPACE));
	Jam::Time::setFPS(60);

#ifdef WIN32
	Jam::Loader::prefix = "../../res/";
#else
	Jam::Loader::prefix = "../res/";
#endif

	std::cout << Jam::Loader::loadText("test.txt") << std::endl;
	
	Jam::Flavor flavor;
	
	flavor.w_width = 1500;
	flavor.w_height = 500;

	flavor.title = "My Test Game";
	flavor.enterState = "test1";
	flavor.transparancy = true;
	flavor.bgColorG = 1;

	Jam::Pie pie(flavor);

	registerStuff();

	pie.bake();

	return 0;
}

void registerStuff()
{
	//Texture: "mario"
	Jam::Texture t_mario;
	t_mario.path = "texture/mario.png";

	Jam::GFXLibrary::registerTexture("mario", t_mario);

	//SpriteSheet: "fire_ball"
	Jam::SpriteSheet ss;
	ss.path = "texture/fire_ball.png";
	ss.tilesX = 6;
	ss.tilesY = 2;

	Jam::GFXLibrary::registerSpriteSheet("fire_ball", ss);
}