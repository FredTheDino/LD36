#pragma once

#include <unordered_map>

#include "gamestate.h"

namespace Jam
{
	class GameState;

	class GameStateLibrary
	{
	public:

		//Registering and fetching game states
		static void registerGameState(std::string tag, GameState* gameState) { _gameStateRegistry.insert(std::make_pair(tag, gameState)); };
		static GameState* getGameState(std::string tag) { return _gameStateRegistry.at(tag); };

	private:

		//Game state map
		static std::unordered_map<std::string, GameState*> _gameStateRegistry;
	};
}