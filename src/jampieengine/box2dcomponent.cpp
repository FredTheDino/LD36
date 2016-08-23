#include "box2dcomponent.h"
#include "entity.h"

using namespace Jam;

Jam::Box2DComponent::Box2DComponent(b2World * world, BodyType type, bool isSensor, 
									float width, float height, 
									float density, float friction, float restitution) {
	b2PolygonShape* shape = new b2PolygonShape;
	shape->SetAsBox(width / 2, height / 2);

	b2BodyDef bodydef;
	switch (type) {
		case Jam::BodyType::DYNAMICBODY:
			bodydef.type = b2BodyType::b2_dynamicBody;
			break;
		case Jam::BodyType::KINEMATIC:
			bodydef.type = b2BodyType::b2_kinematicBody;
			break;
		case Jam::BodyType::STATIC:
			bodydef.type = b2BodyType::b2_staticBody;
			break;
		default:
			break;
	}

	b2FixtureDef fixturedef;
	fixturedef.isSensor = isSensor;
	fixturedef.shape = shape;
	fixturedef.density = density;
	fixturedef.friction = friction;
	fixturedef.restitution = restitution;

	_world = world;
	_bodyDef = new b2BodyDef(bodydef);
	_fixtureDef = new b2FixtureDef(fixturedef);
}

Jam::Box2DComponent::Box2DComponent(b2World * world, BodyType type, bool isSensor, 
									b2Shape * shape, 
									float density, float friction, float restitution) {
	b2BodyDef bodydef;
	switch (type) {
		case Jam::BodyType::DYNAMICBODY:
			bodydef.type = b2BodyType::b2_dynamicBody;
			break;
		case Jam::BodyType::KINEMATIC:
			bodydef.type = b2BodyType::b2_kinematicBody;
			break;
		case Jam::BodyType::STATIC:
			bodydef.type = b2BodyType::b2_staticBody;
			break;
		default:
			break;
	}

	b2FixtureDef fixturedef;
	fixturedef.isSensor = isSensor;
	fixturedef.shape = shape;
	fixturedef.density = density;
	fixturedef.friction = friction;
	fixturedef.restitution = restitution;

	_world = world;
	_bodyDef = new b2BodyDef(bodydef);
	_fixtureDef = new b2FixtureDef(fixturedef);
}

Box2DComponent::Box2DComponent(b2World* world, b2BodyDef bodydef, b2FixtureDef fixturedef) {
	//Copy everything into the object for later processing
	_world = world;
	_bodyDef = new b2BodyDef(bodydef);
	_fixtureDef = new b2FixtureDef(fixturedef);
}

Box2DComponent::~Box2DComponent() {
	_world->DestroyBody(body);
}

void Box2DComponent::_init() {
	//Set the transform to the bodies transform
	Transform t = getParent()->transform;
	_bodyDef->position.Set(t.position.x, t.position.y);
	_bodyDef->angle = t.rotation.z;
	
	//Create the Box2D specific stuff
	body = _world->CreateBody(_bodyDef);
	fixture = body->CreateFixture(_fixtureDef);
	
	//Add a refference to this component
	body->SetUserData(this);

	//Clean up the definers
	delete _bodyDef, _fixtureDef;
}

void Box2DComponent::_update(double delta) {

	//Create a holder for the transform
	Transform transform;
	//Store the bodies transform somewhere close
	b2Transform temp = body->GetTransform();
	//Copy everything over
	transform.position.x = temp.p.x;
	transform.position.y = temp.p.y;
	transform.rotation.z = temp.q.GetAngle();
	//Set the transform
	getParent()->transform = transform;
}

void Jam::Box2DComponent::setBeginContactCallback(void(*begin)(b2Contact *)) {
	_beginContactCallback = begin;
}

void Jam::Box2DComponent::setEndContactCallback(void(*end)(b2Contact *)) {
	_endContactCallback = end;
}
