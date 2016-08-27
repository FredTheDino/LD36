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

	enterRoot("game");
}

void PlayState::update(double delta)
{
	_level->update(delta);
}

void PlayState::exit()
{
	delete _level;
}

void PlayState::_initLevel()
{
	//Level root
	Root* r_level = new Root();
	
	getRoot("game")->addNode(0, "level", r_level);

	//Level
	_level = new Level(r_level, getRenderEngine(), 1);

}

void PlayState::_loadContent()
{
	//Terrain
	RenderEngine::preloadTexture("terrain");


	//Load
	RenderEngine::load();

	while (RenderEngine::remainingLoadEntries() > 0);
}