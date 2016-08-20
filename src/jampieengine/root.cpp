#include "root.h"
#include "root.h"
#include "root.h"

using namespace Jam;

Root::Root() {}

void Root::addNode(int priority, std::string tag, Node* node) {
	_nodes.insert(std::make_pair(tag, node));
	_priorityMap.insert(std::make_pair(priority, tag));
}

void Jam::Root::deleteNode(std::string tag) {
	//Check if it actually exists
	auto ref = _nodes.find(tag);
	if (ref == _nodes.end()) return;

	//BURN IT!
	_nodes.erase(tag);

	//Pummle through everything to DESTROY IT!
	auto it = _priorityMap.begin();
	for (; it != _priorityMap.end(); it++) {
		if (it->second == tag) {
			break;
		}
	}

	//This check is not actually needed, if it exists in the _nodes map
	//it has to exists here, this is only here to prevent possible damage
	if (it != _priorityMap.end())
		_priorityMap.erase(it);
}

void Root::update(double delta)
{
	//Loop through EVERYTHING
	for (auto it = _priorityMap.begin(); it != _priorityMap.end(); it++) {
		_nodes[it->second]->update(delta);
	}
}

Root::~Root()
{
	for (auto it = _nodes.begin(); it != _nodes.end(); it++) {
		//Free allocated memory for the entities
		delete it->second;
	}
	_nodes.clear();
}