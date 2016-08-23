#include "container.h"

using namespace Jam;

void Container::update(double delta)
{
	for (Node* node : _nodes) {
		node->update(delta);
	}
}

void Container::_rootEnter()
{
	for (Node* node : _nodes) {
		node->_rootEnter();
	}
}

void Container::_rootExit()
{
	for (Node* node : _nodes) {
		node->_rootExit();
	}
}