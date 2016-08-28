#include "arrowtrap.h"
#include "arrow.h"

Jam::ArrowTrap::ArrowTrap(RenderEngine * engine, b2World * world, Material material): 
	TrapComponent(engine, material, "fire_spike", 2.0, 0.0, glm::vec2(-0.5), glm::vec2(0.5)) {
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

	Material arrowMaterial;
	arrowMaterial.texture = "default";

	arrow->add(new Arrow(_engine, _world, arrowMaterial, 0));

	GameStateLibrary::getGameState("test")->getRoot("root")->addNode(0, "arrow", (Node*) arrow);
}

void Jam::ArrowTrap::_reset() {}
