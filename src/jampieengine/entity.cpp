#include "entity.h"

using namespace Jam;

Entity::Entity() {}

Entity::~Entity()
{
	for (size_t i = 0; i < _components.size(); i++) {
		_components[i]->_end();
	}

	for (size_t i = 0; i < _components.size(); i++) {
		delete _components[i];
	}
	_components.clear();
}

void Entity::setAll(bool active)
{
	for (size_t i = 0; i < _components.size(); i++) {
		_components[i]->setActive(active);
	}
}

void Entity::toggleAll() {
	for (size_t i = 0; i < _components.size(); i++) {
		_components[i]->toggleActive();
	}
}

void Entity::update(double delta)
{
	for (size_t i = 0; i < _components.size(); i++) {
		_components[i]->_update(delta);
	}

}