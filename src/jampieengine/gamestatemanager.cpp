#include "gamestatemanager.h"

using namespace Jam;

bool GameStateManager::_shouldUpdate = true;

GameStateManager::GameStateManager(Pie& pie, GameState* gameState)
	: _pie(pie)
{
	enterState(gameState);
}

void GameStateManager::update(double delta)
{

	if (_shouldEnterNewState) {
		_enterState();
	}

	RenderEngine::setShouldRender(true);
	while (!_shouldUpdate && Pie::isCooking());

	if (_currentState != nullptr) {
		GameState* state = _currentState;
		state->update(delta);
		state->_updateRoot(delta);
	}

	if (RenderEngine::avoidConflicts) {
		RenderEngine::cancelRendering();
		RenderEngine::avoidConflicts = false;
	}

	_shouldUpdate = false;
	while (RenderEngine::shouldRender() && Pie::isCooking());
}

void GameStateManager::enterState(std::string tag)
{
	enterState(GameStateLibrary::getGameState(tag));
}

void GameStateManager::enterState(GameState* gameState)
{
	_stateToEnter = gameState;
	_shouldEnterNewState = true;
}

void GameStateManager::_enterState()
{
	if (_currentState != nullptr) {
		_currentState->_currentRoot->_rootExit();
		_currentState->exit();
		_currentState->_roots.clear();
	}

	_currentState = _stateToEnter;

	_currentState->_setGameStateManager(this);
	_currentState->_setRenderEngine(_pie.getGraphicsCore()->getRenderEngine());
	_currentState->init();

	_shouldEnterNewState = false;
}

GameStateManager::~GameStateManager()
{

}