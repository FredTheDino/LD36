#include "arrow.h"
#include "box2dcomponent.h"
#include "entity.h"
#include "Box2D/Box2D.h"
#include "adventurer.h"

using namespace Jam;

void arrowDeathCallback(b2Contact* contact) {

	Entity* bodyA = ((Box2DComponent*) contact->GetFixtureA()->GetBody()->GetUserData())->getParent();
	Adventurer* adventurer;
	adventurer = bodyA->get<Adventurer>();

	if (!adventurer) {
		Entity* bodyB = ((Box2DComponent*) contact->GetFixtureB()->GetBody()->GetUserData())->getParent();
		adventurer = bodyB->get<Adventurer>();
	}

	if (!adventurer) { return; }
	if (!adventurer->isActive()) { return; }

	adventurer->die(Death::PHYSICAL);
}

Jam::Arrow::Arrow(RenderEngine * engine, b2World * world, float direction): Component() {
	_world = world;
	_engine = engine;
	_direction = direction;
}

Jam::Arrow::~Arrow() {}

void Jam::Arrow::_init() {
	Material material;
	material.texture = "arrow";

	getParent()->add(new Renderer(_engine, 10, "quad", material));

	//getParent()->scale(0.2, 0.4);

	b2BodyDef body;
	body.bullet = true;
	body.type = b2BodyType::b2_dynamicBody;
	body.gravityScale = 0.5;
	body.linearDamping = 0.2;

	b2PolygonShape shape;
	shape.SetAsBox(0.1, 0.2);

	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 0.01;
	fixture.friction = 1;

	getParent()->rotate(_direction);
	getParent()->add(new Box2DComponent(_world, body, fixture));
	_direction += 0.5 * M_PI;
	b2Vec2 force(_speed * cos(_direction), _speed * sin(_direction));
	getParent()->get<Box2DComponent>()->body->ApplyLinearImpulseToCenter(force, true);
	getParent()->get<Box2DComponent>()->setBeginContactCallback(arrowDeathCallback);
}

void Jam::Arrow::_update(double delta) {
	_time += delta;
	if (!getParent()->get<Box2DComponent>()->body->IsAwake() || _lifeTime < _time) {
		b2Filter filter;
		filter.maskBits = 0x0000000;
		getParent()->get<Box2DComponent>()->fixture->SetFilterData(filter);
		getParent()->get<Box2DComponent>()->body->SetGravityScale(0);
	}
}

void Jam::Arrow::_end() {}
