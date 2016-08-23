#include "entity.h"
#include "renderer.h"

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
	if (has<Renderer>())
		while (get<Renderer>()->shouldDraw());

	for (size_t i = 0; i < _components.size(); i++) {
		_components[i]->_update(delta);
	}

	if (has<Renderer>())
		get<Renderer>()->setShouldDraw(true);
}

void Entity::_rootEnter()
{
	for (size_t i = 0; i < _components.size(); i++) {
		_components[i]->_rootEnter();
	}
}

void Entity::_rootExit()
{
	for (size_t i = 0; i < _components.size(); i++) {
		_components[i]->_rootExit();
	}
}