#include "arrowtrap.h"
#include "arrow.h"
#include "container.h"

Jam::ArrowTrap::ArrowTrap(RenderEngine * engine, b2World * world, Material material): 
	TrapComponent(engine, material, "fire_spike", 1.0, 0.0, glm::vec2(-0.5), glm::vec2(0.5)) {
	_world = world;
}

Jam::ArrowTrap::~ArrowTrap() {}

void Jam::ArrowTrap::_init() {
	TrapComponent::_init();
}

void Jam::ArrowTrap::_update(double delta) {
	TrapComponent::_update(delta);
}

void Jam::ArrowTrap::_end() {}

void Jam::ArrowTrap::_fire() {

	Entity* arrow = new Entity();

	float angle = getParent()->getRotation().z;

	arrow->add(new Arrow(_engine, _world, angle));
	arrow->move(getParent()->getPosition());
	angle += 0.5 * M_PI;
	arrow->move(cos(angle), sin(angle));

	((Container*)GameStateLibrary::getGameState("test")->getRoot("root")->getNode("arrowContainer"))->addNode((Node*) arrow);
	arrow->_rootEnter();
}

void Jam::ArrowTrap::_reset() {}
