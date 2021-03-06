#include "teststate.h"

#include "box2dcomponent.h"
#include "spiketrap.h"
#include "renderer.h"
#include "adventurer.h"
#include "box2dlistener.h"
#include "arrowtrap.h"
#include "container.h"
#include "firetrap.h"

Jam::Box2DListener listener;

void Jam::TestState::init() {
	_initTestStuff();

	enterRoot("root");
}

void Jam::TestState::update(double deta) {
	_world->Step(deta, 8, 2);
}

void Jam::TestState::exit() {}

void Jam::TestState::_initTestStuff() {

	/*
	RenderEngine::preloadSpriteSheet("spike_trap");
	RenderEngine::preloadTexture("arrow");
	RenderEngine::preloadTexture("arrow_trap");

	*/
	RenderEngine::load();

	while (RenderEngine::remainingLoadEntries() > 0) {}

	//Add root
	Root* root = new Root();

	_world = new b2World(b2Vec2(0, -9.82));
	_world->SetContactListener(&listener);

	//Floor
	Entity* floor = new Entity();

	floor->setPosition(glm::vec3(0, 0, 0));

	Material mat;
	mat.texture = "default";
	mat.baseColor.x = 0.5;
	mat.baseColor.y = 0.5;

	b2PolygonShape shape;
	shape.SetAsBox(5, 1);
	floor->scale(10, 1);

	floor->add(new Box2DComponent(_world, Jam::BodyType::STATIC, false, &shape));
	floor->add(new Renderer(getRenderEngine(), 0, "quad", mat));

	root->addNode(0, "floor", (Node*) floor);

	//Add containers for the traps
	Container* arrowContainer = new Container();
	root->addNode(0, "arrowContainer", (Node*) arrowContainer);

	Container* flameContainer = new Container();
	root->addNode(0, "flameContainer", (Node*) flameContainer);

	//Trap
	Entity* trap = new Entity();
	trap->scale(1);
	//trap->move(-3, 1.5);

	Material spikeMaterial;
	spikeMaterial.texture = "arrow_trap";
	/*spikeMaterial.spriteSheet = true;
	spikeMaterial.ssOffsetX = 0;
	spikeMaterial.ssOffsetY = 0;
	*/

	trap->add(new SpikeTrap(getRenderEngine(), _world, spikeMaterial));
	trap->rotate(-0.5 * M_PI);
	root->addNode(0, "trap", (Node*) trap);

	//The adventurer
	Entity* adventurer = new Entity();
	adventurer->move(0, 5);

	/*
	adventurer->add(new Adventurer(getRenderEngine(), _world));

	root->addNode(0, "adventurer", (Node*) adventurer);
	*/

	getRenderEngine()->getCamera()->transform.scaleT(8);
	InputHandler::registerInput("fire_spike", InputBinding(3));
	
	addRoot("root", root);
}
