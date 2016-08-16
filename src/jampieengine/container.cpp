#include "container.h"

using namespace Jam;

void Container::update(double delta)
{
	for (Node* node : _nodes) {
		node->update(delta);
	}
}