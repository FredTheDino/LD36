#include "pie.h"

#include <SDL2/SDL.h>
#include "loader.h"

#include "gamestate.h"
#include "gamestatelibrary.h"

#include "menustate.h"
#include "playstate.h"
#include "teststate.h"

void registerTextures();
void registerSpriteSheets();

int main(int c, char** args) {
	Jam::GameStateLibrary::registerGameState("menu", (Jam::GameState*) new MenuState());
	Jam::GameStateLibrary::registerGameState("play", (Jam::GameState*) new PlayState());
	Jam::GameStateLibrary::registerGameState("test", (Jam::GameState*) new Jam::TestState());

	Jam::Time::setFPS(120);

#ifdef WIN32
	Jam::Loader::prefix = "../../res/";
#else
	Jam::Loader::prefix = "../res/";
#endif

	Jam::Flavor flavor;
	flavor.w_width = 1280;
	flavor.w_height = 720;

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
	
	//coins_on
	Jam::Texture t_coins_on;
	t_coins_on.path = "texture/gui/shop/coins_on.png";

	Jam::GFXLibrary::registerTexture("coins_on", t_coins_on);

	//coins_off
	Jam::Texture t_coins_off;
	t_coins_off.path = "texture/gui/shop/coins_off.png";

	Jam::GFXLibrary::registerTexture("coins_off", t_coins_off);
	
	
	//coins_map
	Jam::Texture t_coins_map;
	t_coins_map.path = "texture/gui/shop/coins_map.png";

	Jam::GFXLibrary::registerTexture("coins_map", t_coins_map);

	//Traps
	//arrow_trap
	Jam::Texture t_arrowTrap;
	t_arrowTrap.path = "texture/traps/arrow_trap.png";

	Jam::GFXLibrary::registerTexture("arrow_trap", t_arrowTrap);

	//arrow
	Jam::Texture t_arrow;
	t_arrow.path = "texture/traps/arrow.png";

	Jam::GFXLibrary::registerTexture("arrow", t_arrow);
}

void registerSpriteSheets()
{
	//Traps
	//spike_trap
	Jam::SpriteSheet ss_spikes;
	ss_spikes.path = "texture/traps/spikes.png";
	ss_spikes.tilesX = 2;
	ss_spikes.tilesY = 1;

	Jam::GFXLibrary::registerSpriteSheet("spike_trap", ss_spikes);
}