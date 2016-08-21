#include "gamestate.h"

using namespace Jam;

GameState::GameState()
{
	
}

void GameState::_updateRoot(double delta)
{
	if(_currentRoot != nullptr)
		_currentRoot->update(delta);
}

void GameState::enterRoot(std::string tag)
{
	_currentRoot = _roots.at(tag);
}

GameState::~GameState()
{
	
}