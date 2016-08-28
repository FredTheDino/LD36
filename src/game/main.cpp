#include "pie.h"

#include <SDL2/SDL.h>
#include "loader.h"

#include "gamestate.h"
#include "gamestatelibrary.h"

#include "menustate.h"
#include "playstate.h"

void registerTextures();
void registerSpriteSheets();

int main(int c, char** args) {
	Jam::GameStateLibrary::registerGameState("menu", (Jam::GameState*) new MenuState());
	Jam::GameStateLibrary::registerGameState("play", (Jam::GameState*) new PlayState());

	//Jam::Time::setFPS(60);

#ifdef WIN32
	Jam::Loader::prefix = "../../res/";
#else
	Jam::Loader::prefix = "../res/";
#endif

	Jam::Flavor flavor;
	flavor.w_width = 800;
	flavor.w_height = 600;

	flavor.title = "LD36";
	flavor.enterState = "menu";
	flavor.transparancy = true;
	flavor.bgColorR = 1.0f;
	flavor.bgColorG = 0.94f;
	flavor.bgColorB = 0.65f;

	Jam::Pie pie(flavor);

	registerTextures();
	registerSpriteSheets();

	pie.bake();

	return 0;
}

void registerTextures()
{
	//button_play
	Jam::Texture t_buttonPlay;
	t_buttonPlay.path = "texture/gui/button_play.png";

	Jam::GFXLibrary::registerTexture("button_play", t_buttonPlay);

	//button_exit
	Jam::Texture t_buttonExit;
	t_buttonExit.path = "texture/gui/button_exit.png";

	Jam::GFXLibrary::registerTexture("button_exit", t_buttonExit);

	//terrain
	Jam::Texture t_terrain;
	t_terrain.path = "texture/terrain.png";

	Jam::GFXLibrary::registerTexture("terrain", t_terrain);

	//shop icons
	for (int i = 0; i < Shop::ITEM_COUNT; i++) {

		std::string id = std::to_string(i);

		Jam::Texture t_icon_off;
		t_icon_off.path = "texture/gui/shop/" + id + "_off.png";

		Jam::Texture t_icon_on;
		t_icon_on.path = "texture/gui/shop/" + id + "_on.png";

		Jam::GFXLibrary::registerTexture(id + "_off", t_icon_off);
		Jam::GFXLibrary::registerTexture(id + "_on", t_icon_on);
	}
}

void registerSpriteSheets()
{
	
}