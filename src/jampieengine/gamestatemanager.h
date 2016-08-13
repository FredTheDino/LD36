#pragma once

#include "pie.h"
#include "gamestate.h"
#include "gamestatemanager.h"

namespace Jam
{
	//Forward declarations
	class Pie;
	class GameState;

	class GameStateManager
	{
	public:
		GameStateManager(Pie& pie);
		~GameStateManager();

		void update();

		void enterState(std::string tag) { enterState(GameStateLibrary::getGameState(tag)); };
		void enterState(GameState* gameState);

	private:

		Pie& _pie;

	};
}