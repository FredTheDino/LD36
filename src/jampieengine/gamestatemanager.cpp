#include "gamestatemanager.h"

using namespace Jam;

GameStateManager::GameStateManager(Pie& pie, GameState* gameState)
	: _pie(pie)
{
	enterState(gameState);
}

void GameStateManager::update(double delta)
{
	if (_currentGameState != nullptr) {
		_currentGameState->update(delta);
		_currentGameState->_updateRoot(delta);
	}
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

	_currentGameState->_setGameStateManager(this);
	_currentGameState->_setRenderEngine(_pie.getGraphicsCore()->getRenderEngine());
	_currentGameState->init();
}

GameStateManager::~GameStateManager()
{

}