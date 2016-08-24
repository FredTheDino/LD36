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
	if (_currentRoot != nullptr)
		_currentRoot->_rootExit();

	_currentRoot = _roots.at(tag);

	_currentRoot->_rootEnter();
}

GameState::~GameState()
{
	
}