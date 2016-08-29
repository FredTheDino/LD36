#include "adventurer.h"
#include "Box2D/Box2D.h"
#include "box2dcomponent.h"

Jam::Adventurer::Adventurer(RenderEngine * engine, b2World * world) {
	_engine = engine;
	_world = world;
}

Jam::Adventurer::~Adventurer() {}

void Jam::Adventurer::_init() {
	getParent()->scale(1);
	getParent()->add(new Renderer(_engine, 5, "quad", "default"));
	getParent()->add(new Box2DComponent(_world, BodyType::DYNAMICBODY, false, 0.5, 0.5, 0.5, 0.0, 0.0));

#if 0

	for (size_t x = 0; x < CHUNKS_X; x++) {
		for (size_t y = 0; y < CHUNKS_Y; y++) {
			_map[x][y] = MapNotation();
		}
	}

#endif
}

void Jam::Adventurer::_update(double delta) {
	getParent()->get<Box2DComponent>()->body->ApplyForceToCenter(b2Vec2(25.0 * delta, 0.0), true);
#if 0




#endif
}

void Jam::Adventurer::_end() {}

void Jam::Adventurer::die(Death death) {
	printf("An adventurer died");
}
