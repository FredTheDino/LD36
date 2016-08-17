#pragma once

#include "gamestate.h"
#include "node.h"

namespace Jam
{
	//Forward declarations
	class GameState;

	class Root
	{
	public:
		Root(GameState& gameState);
		~Root();

		void update(double delta);

		void addNode(int priority, std::string tag, Node* node) { _nodes.insert(std::make_pair(tag, node)); _priorities.insert(std::make_pair(priority, tag)); };

		Node* getNode(std::string tag) { return _nodes.at(tag); };

	private:
		GameState& _gameState;

		std::unordered_map<std::string, Node*> _nodes;
		
		std::map<int, std::string, std::less<int>> _priorities;
	};
}