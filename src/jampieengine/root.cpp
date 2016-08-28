#include "root.h"

using namespace Jam;

Root::Root() {}

void Root::addNode(int priority, std::string tag, Node* node) {
	_nodes.insert(std::make_pair(tag, node));
	_priorityMap.insert(std::make_pair(priority, tag));
}

void Jam::Root::deleteNode(std::string tag) {
	//Add it to the trash heap
	_trash.push_back(tag);
}

void Root::_rootEnter()
{
	for (auto it = _priorityMap.begin(); it != _priorityMap.end(); it++) {
		_nodes[it->second]->_rootEnter();
	}
}

void Root::_rootExit()
{
	for (auto it = _priorityMap.begin(); it != _priorityMap.end(); it++) {
		_nodes[it->second]->_rootExit();
	}
}

void Root::update(double delta)
{
	//Loop through EVERYTHING
	for (auto it = _priorityMap.begin(); it != _priorityMap.end(); it++) {
		_nodes[it->second]->update(delta);
	}

	//Check the trash
	if (_trash.size()) {
		//If it existst, clear it before the next update
		std::string tag = "";
		for (size_t i = 0; i < _trash.size(); i++) {

			tag = _trash[i];

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

		_trash.clear();
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