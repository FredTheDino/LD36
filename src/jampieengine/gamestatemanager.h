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
		GameStateManager(Pie& pie, GameState* gameState);
		~GameStateManager();

		void update(double delta);

		void enterState(std::string tag);
		void enterState(GameState* gameState);

		Pie& getPie() { return _pie; };

		static bool shouldUpdate() { return _shouldUpdate; };
		static void setShouldUpdate(bool shouldUpdate) { _shouldUpdate = shouldUpdate; };

	private:

		static bool _shouldUpdate;

		void _enterState();
		bool _shouldEnterNewState = false;

		Pie& _pie;

		GameState* _currentState = nullptr;
		GameState* _stateToEnter = nullptr;

	};
}