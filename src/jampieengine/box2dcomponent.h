#pragma once

#include "Box2D/Box2D.h"
#include "component.h"

#include <vector>

namespace Jam {
	enum class BodyType {
		DYNAMICBODY,
		KINEMATIC,
		STATIC
	};

	class Box2DComponent: public Component {

		class Box2DListener;
	public:
		Box2DComponent(b2World* world, BodyType type, bool isSensor, float width, float height, 
					   float density = 1.0, float friction = 1.0, float restitution = 0.0);
		Box2DComponent(b2World* world, BodyType type, bool isSensor, b2Shape* shape, 
					   float density = 1.0, float friction = 1.0, float restitution = 0.0);
		Box2DComponent(b2World* world, b2BodyDef bodydef, b2FixtureDef fixturedef);
		~Box2DComponent();

		//Unimplemented
		void _end() {}

		//Initalizes the Box2D components
		void _init();

		//The update loop
		void _update(double delta);

		//A public Box2D refferences
		b2Body* body;
		b2Fixture* fixture;

		//Set the begin contact callback
		void setBeginContactCallback(void(*begin) (b2Contact*));
		//Set the end contact callback
		void setEndContactCallback(void(*end) (b2Contact*));

		//The begin contact callback
		void (*_beginContactCallback) (b2Contact*) = 0;
		//The end contact callback
		void (*_endContactCallback) (b2Contact*) = 0;

	private:
		
		//Remember the deffinitions until _init, so we can get the entity
		b2BodyDef* _bodyDef;
		b2FixtureDef* _fixtureDef;

		//A pointer to the physics world
		b2World* _world;

		friend Box2DListener;
	};
}