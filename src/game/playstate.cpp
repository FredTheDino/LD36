#include "playstate.h"

using namespace Jam;

void PlayState::init()
{
	_loadContent();

	//Main root
	Root* game = new Root();

	//Add root
	addRoot("game", game);

	_initLevel();

	Jam::InputHandler::registerInput("switch", Jam::InputBinding(true, SDLK_k));

	enterRoot("game");
}

void PlayState::update(double delta)
{
	/*if (_initNewLevel) {
		RenderEngine::avoidConflicts = true;
		_initLevel();
		_initNewLevel = false;
	}*/

	if (Jam::InputHandler::keyPressed("switch")) {
		//_level->complete();
		//delete _level;
		//getRoot("game")->getNode("level")->_rootExit();
		//getRoot("game")->deleteNode("level");
		_initNewLevel = true;
		_gameStateManager->enterState("play");
		return;
	}

	_level->update(delta);
}

void PlayState::exit()
{
	delete _level;
	_unloadContent();
}

void PlayState::_initLevel()
{
	//Level root
	Root* r_level = new Root();
	
	getRoot("game")->addNode(0, "level", r_level);

	//Level
	_level = new Level(r_level, getRenderEngine(), _difficulty++);

}

void PlayState::_loadContent()
{
	//Terrain
	RenderEngine::preloadTexture("terrain");

	//Coins
	RenderEngine::preloadTexture("coins_on");
	RenderEngine::preloadTexture("coins_off");
	RenderEngine::preloadTexture("coins_map");


	//Load
	RenderEngine::load();

	while (RenderEngine::remainingLoadEntries() > 0);
}

void PlayState::_unloadContent()
{
	RenderEngine::unloadMesh("level_terrain");

	GFXLibrary::removeMesh("level_terrain");
}