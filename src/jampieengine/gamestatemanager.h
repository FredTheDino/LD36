#pragma once

#include "pie.h"
#include "gamestate.h"
#include "gamestatelibrary.h"

namespace Jam
{
	//Forward declarations
	class Pie;
	class GameState;
	class GameStateLibrary;

	class GameStateManager
	{
	public:
		GameStateManager(Pie& pie);
		~GameStateManager();

		void update();

		void enterState(std::string tag);
		void enterState(GameState* gameState);

	private:

		Pie& _pie;

		GameState* _currentGameState;

	};
}