#pragma once

#include <vector>

#include "gamestatemanager.h"
#include "root.h"

namespace Jam
{
	//Forward declarations
	class GameStateManager;
	class Root;

	class GameState
	{
	public:
		GameState();
		~GameState();

		virtual void init() = 0;
		virtual void update(double delta) = 0;
		virtual void exit() = 0;

		void addRoot(std::string tag, Root* root) { _roots.insert(std::make_pair(tag, root)); };
		void removeRoot(std::string tag) { _roots.erase(tag); };
		Root* getRoot(std::string tag) { return _roots.at(tag); };

		void enterRoot(std::string tag);

		Root* getCurrentRoot() { return _currentRoot; };

	protected:
		GameStateManager* _gameStateManager;


	private:

		Root* _currentRoot = nullptr;

		std::unordered_map<std::string, Root*> _roots;

		void _setGameStateManager(GameStateManager* gameStateManager) { _gameStateManager = gameStateManager; };
		void _updateRoot(double delta);
		
		friend GameStateManager;
	};
}