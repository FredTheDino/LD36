#pragma once

#include "pie.h"

#include "gamestate.h"
#include "gamestatelibrary.h"
#include "root.h"
#include "entity.h"
#include "node.h"
#include "component.h"
#include "audiohandler.h"
#include "soundsource.h"

#include "testcomponent.h"

class TestState: Jam::GameState {
public:
	void init() {
		std::cout << "Test1: Adding roots..." << std::endl;

		root = new Jam::Root(*this);

		Jam::Entity* entity = new Jam::Entity();

		entity->add(new Jam::SoundSource());
		entity->add(new TestComponent());

		root->addNode(1, "TestEntity", (Jam::Node*) entity);
		addRoot("TestRoot", root);

		enterRoot("TestRoot");
	}

	void update(double delta) {
		if (Jam::InputHandler::checkInputState("t_reset", Jam::KeyState::PRESSED))
			((Jam::Entity*) getCurrentRoot()->getNode("TestEntity"))->get<TestComponent>()->reset();
	}

	void exit() {
		removeRoot("TestRoot");
		delete root;
	}

private:
	Jam::Root* root = nullptr;
};