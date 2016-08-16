#pragma once

#include <vector>

#include "node.h"

namespace Jam
{
	class Container : Node
	{
	public:

		void addNode(Node* node) { _nodes.push_back(node); };

		void update(double delta);

	private:

		std::vector<Node*> _nodes;

	};
}