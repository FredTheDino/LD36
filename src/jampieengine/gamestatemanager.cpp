#include "gamestatemanager.h"

using namespace Jam;

GameStateManager::GameStateManager(Pie& pie)
	: _pie(pie)
{

}

void GameStateManager::update()
{

}

void GameStateManager::enterState(std::string tag)
{
	enterState(GameStateLibrary::getGameState(tag));
}

void GameStateManager::enterState(GameState* gameState)
{
	if (_currentGameState != nullptr)
		_currentGameState->exit();

	_currentGameState = gameState;
}

GameStateManager::~GameStateManager()
{

}