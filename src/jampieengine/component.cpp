#include"component.h"
#include "entity.h"

void Jam::Component::setActive(bool active)
{
	_isActive = active;
}

void Jam::Component::toggleActive()
{
	_isActive = !_isActive;
}

bool Jam::Component::isActive()
{
	return _isActive;
}

Jam::Entity* Jam::Component::_getParent()
{
	return _parent;
}

void Jam::Component::_setParent(Jam::Entity* parent)
{
	_parent = parent;
}