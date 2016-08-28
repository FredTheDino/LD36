#pragma once

#include "gamestate.h"

#include "level.h"

class PlayState : Jam::GameState
{
public:

	void init();
	void update(double delta);
	void exit();

private:

	unsigned int _difficulty = 0;

	Level* _level;

	void _loadContent();

	void _initLevel();

};