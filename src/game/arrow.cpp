#include "arrow.h"
#include "box2dcomponent.h"

Jam::Arrow::Arrow(RenderEngine * engine, b2World * world, Material material, float direction): Component() {
	_world = world;
	_engine = engine;
	_material = material;
	_direction = direction;
}

Jam::Arrow::~Arrow() {}

void Jam::Arrow::_init() {
	getParent()->add(new Renderer(_engine, 10, "quad", _material));

	b2BodyDef body;
	body.bullet = true;
	
	b2PolygonShape shape;
	shape.SetAsBox(0.1, 0.1);

	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 0.1;

	getParent()->add(new Box2DComponent(_world, body, fixture));
	getParent()->rotate(_direction);
	b2Vec2 force(_speed * sin(_direction), _speed * cos(_direction));
	getParent()->get<Box2DComponent>()->body->ApplyLinearImpulseToCenter(force, true);
}

void Jam::Arrow::_update(double delta) {
	if (!getParent()->get<Box2DComponent>()->body->IsAwake()) {
		printf("Delete entity!");
		GameStateLibrary::getGameState("test")->getRoot("root")->deleteNode("arrow");
	}
}

void Jam::Arrow::_end() {}
