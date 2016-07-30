#include"component.h"
#include "entity.h"

void Component::setParent(Entity& parent) {
	_parent = &parent;
}

Component::Component(ComponentTypes type): _type(type) {}