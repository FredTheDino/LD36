#pragma once

#include <vector>

#include "node.h"

namespace Jam
{
	class Node;

	class Container : Node
	{
	public:

		void addNode(Node* node) { _nodes.push_back(node); };

		void update(double delta);

		void _rootEnter();
		void _rootExit();

	private:

		std::vector<Node*> _nodes;

	};
}