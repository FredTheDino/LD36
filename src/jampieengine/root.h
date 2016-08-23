#pragma once

//This would make the linking brake if "node.h"
// is included before gamestate.h.
//#include "gamestate.h"
#include "node.h"

#include <string>
#include <map>
#include <unordered_map>

namespace Jam
{
	//Forward declarations
	class GameState;

	class Root : public Node
	{
	public:
		Root();
		~Root();

		//Update all entities
		void update(double delta);

		//Add a node to the entity tree
		void addNode(int priority, std::string tag, Node* node);

		//Return a node from the node tree
		Node* getNode(std::string tag) { return _nodes.at(tag); };

		//Delete a node
		void deleteNode(std::string tag);

	private:

		//A list holding all nodes
		std::unordered_map<std::string, Node*> _nodes;
		//A list that holds the update order of the nodes
		std::multimap<int, std::string> _priorityMap;
	};
}