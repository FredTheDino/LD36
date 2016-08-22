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
#include "audiocomponenttest.h"

#include "testcomponent.h"

#include "box2dlistener.h"
#include "box2dcomponent.h"
#include "Box2D/Box2D.h"

void col(b2Contact* contact) {
	std::cout << "y: " << contact->GetFixtureA()->GetBody()->GetTransform().p.y << std::endl;
}

class TestState: Jam::GameState {
public:

	void init() {
		std::cout << "Test1: Adding roots..." << std::endl;

		root = new Jam::Root();

		Jam::Entity* entity = new Jam::Entity();

		Jam::Entity* body = new Jam::Entity();
		Jam::Entity* floor = new Jam::Entity();

		_world = new b2World(b2Vec2(0, -9.82));

		_world->SetContactListener(&_listener);

		body->transform.position.x = 0;
		body->transform.position.y = 10;
		 
		body->add(new Jam::Box2DComponent(_world, Jam::BodyType::DYNAMICBODY, false, 2.0f, 2.0f, 1.0, 1.0, 1.0));
		body->get<Jam::Box2DComponent>()->setBeginContactCallback(&col);

		b2BodyDef bodyDef;
		b2FixtureDef fixtureDef;
		
		bodyDef.type = b2BodyType::b2_staticBody;
		{
			b2PolygonShape* s = new b2PolygonShape;
			s->SetAsBox(10, 0.5);
			fixtureDef.shape = s;
		}

		floor->transform.position.x = 0;
		floor->transform.position.y = 0;

		floor->add(new Jam::Box2DComponent(_world, bodyDef, fixtureDef));

		body->add(new AudioComponentTest());
		entity->add(new TestComponent());

		root->addNode(1, "floor", (Jam::Node*) floor);
		root->addNode(1, "bod", (Jam::Node*) body);
		root->addNode(1, "TestEntity", (Jam::Node*) entity);
		addRoot("TestRoot", root);

		enterRoot("TestRoot");
	}

	void update(double delta) {
		if (Jam::InputHandler::checkInputState("t_reset", Jam::KeyState::PRESSED))
			((Jam::Entity*) getCurrentRoot()->getNode("TestEntity"))->get<TestComponent>()->reset();
		_world->Step(delta, 3, 8);
	}

	void exit() {
		removeRoot("TestRoot");
		delete root;
		delete _world;
	}

private:
	Jam::Root* root = nullptr;
	Jam::Box2DListener _listener;
	b2World* _world;
};