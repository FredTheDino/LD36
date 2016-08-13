#pragma once

#include <vector>

#include "gamestatemanager.h"

namespace Jam
{
	//Forward declarations
	class GameStateManager;

	class GameState
	{
	public:
		GameState(GameStateManager& gameStateManager);
		~GameState();

		virtual void init() = 0;
		virtual void update() = 0;
		virtual void exit() = 0;

	protected:
		GameStateManager& _gameStateManager;


		
	};
}