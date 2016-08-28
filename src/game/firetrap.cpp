#include "firetrap.h"
#include "box2dcomponent.h"
#include "gamestatemanager.h"
#include "container.h"
#include "entity.h"
#include "Box2D/Box2D.h"
#include "adventurer.h"

using namespace Jam;

void fireDeathCallback(b2Contact* contact) {

	Entity* bodyA = ((Box2DComponent*) contact->GetFixtureA()->GetBody()->GetUserData())->getParent();
	Adventurer* adventurer;
	adventurer = bodyA->get<Adventurer>();

	if (!adventurer) {
		Entity* bodyB = ((Box2DComponent*) contact->GetFixtureB()->GetBody()->GetUserData())->getParent();
		adventurer = bodyB->get<Adventurer>();
	}

	if (!adventurer) { return; }
	if (!adventurer->isActive()) { return; }

	adventurer->die(Death::FIRE);
}

Jam::FireTrap::FireTrap(RenderEngine* engine, b2World* world, Root* root): 
	TrapComponent(engine, Material(), "fire_spike"/*"fire_fire"*/, 2.0, 2.0, glm::vec2(-0.5), glm::vec2(0.5))  {
	_world = world;
	_root = root;
}

Jam::FireTrap::~FireTrap() {}

void Jam::FireTrap::_init() {
	//_material.texture = "fire_trap";
	_material.texture = "default";
	_material.baseColor = glm::vec4(0.2, 0.7, 0.0, 1.0);
	
	TrapComponent::_init();

	//Init the flame component
	_flame = new Entity();

	//Set up the graphics
	Material flameMaterial;
	flameMaterial.texture = "default";
	flameMaterial.baseColor = glm::vec4(0.8, 0.2, 0.2, 1.0);

	_flame->add(new Renderer(_engine, 11, "quad", flameMaterial));
	
	//Fix the collider
	b2BodyDef bodyDef;
	bodyDef.type = b2BodyType::b2_staticBody;
	
	b2FixtureDef fixtureDef;
	fixtureDef.isSensor = true;
	fixtureDef.filter.maskBits = 0x000000;
	
	b2PolygonShape shape;
	shape.SetAsBox(0.5, 0.5);
	fixtureDef.shape = &shape;
	
	_flame->add(new Box2DComponent(_world, bodyDef, fixtureDef));
	_flame->get<Box2DComponent>()->setBeginContactCallback(fireDeathCallback);

	//Move it
	float angle = getParent()->getRotation().z;
	angle += 0.5 * M_PI;
	_flame->move(getParent()->getPosition());
	_flame->move(cos(angle), sin(angle));

	_flame->setAll(false);
	((Container*) _root->getNode("flameContainer"))->addNode((Node*) _flame);
	//_flame->_rootEnter();
}

void Jam::FireTrap::_update(double delta) {
	TrapComponent::_update(delta);
}

void Jam::FireTrap::_end() {}

void Jam::FireTrap::_fire() {
	b2Filter filter;
	filter.maskBits = 0xFFFFFF;
	_flame->get<Box2DComponent>()->fixture->SetFilterData(filter);
	_flame->setAll(true);
	printf("FIRE!!!");
}

void Jam::FireTrap::_reset() {
	b2Filter filter;
	filter.maskBits = 0x000000;
	_flame->get<Box2DComponent>()->fixture->SetFilterData(filter);
	_flame->setAll(false);
}
