#include "spiketrap.h"
#include "Box2D/Box2D.h"
#include "box2dcomponent.h"
#include "entity.h"
#include "adventurer.h"

namespace Jam {
	void fireDeathCallback(b2Contact* contact) {

		Entity* bodyA = ((Box2DComponent*)contact->GetFixtureA()->GetBody()->GetUserData())->getParent();
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
	
		
	SpikeTrap::SpikeTrap(RenderEngine* engine, b2World* world, Material material): 
		TrapComponent(engine, material, "fire_spike" , 2.0f, 1.0f, glm::vec2(-0.5), glm::vec2(0.5)) {
		_world = world;
	}

  SpikeTrap::~SpikeTrap() {}

  void SpikeTrap::_init() {
	  b2BodyDef body;
	  body.type = b2BodyType::b2_staticBody;

	  b2PolygonShape shape;
	  shape.SetAsBox(0.5, 0.5);

	  b2FixtureDef fixture;
	  fixture.isSensor = true;
	  fixture.shape = &shape;

	  Box2DComponent* b = new Box2DComponent(_world, body, fixture);
	  getParent()->add(b);
	  b->setBeginContactCallback(fireDeathCallback);
  }

  void SpikeTrap::_update(double delta) {
	  TrapComponent::_update(delta);
  }
  
  void SpikeTrap::_fire() {
	  b2Filter filter;
	  filter.maskBits = 0xFFFFFF;
	  getParent()->get<Box2DComponent>()->fixture->SetFilterData(filter);
  }

  void SpikeTrap::_reset() {
	  b2Filter filter;
	  filter.maskBits = 0x000000;
	  getParent()->get<Box2DComponent>()->fixture->SetFilterData(filter);
  }
}
