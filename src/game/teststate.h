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
#include "renderer.h"

#include "testcomponent.h"

#include "box2dlistener.h"
#include "box2dcomponent.h"
#include "Box2D/Box2D.h"
#include "inputhandler.h"
#include "material.h"

void col(b2Contact* contact) {
	std::cout << "HIT!" << std::endl;
}

class TestState: Jam::GameState
{
public:

	void init()
	{
		Jam::Root* root = new Jam::Root();

		loadStuff();

		Jam::Entity* entity = new Jam::Entity();
		entity->add(new TestComponent(getRenderEngine()->getCamera()));

		Jam::Material material;
		material.texture = "metal";

		entity->add(new Jam::Renderer(getRenderEngine(), "quad", material));

		root->addNode(0, "t_metal", (Jam::Node*) entity);

		Jam::Entity* mario = new Jam::Entity();
		mario->add(new TestComponent(getRenderEngine()->getCamera()));
		
		Jam::Material material_mario;
		material_mario.texture = "mario";

		mario->add(new Jam::Renderer(getRenderEngine(), "quad", material_mario));

		root->addNode(0, "t_mario", (Jam::Node*) mario);

		mario->transform.translateX(.5f);

		addRoot("t_root", root);

		enterRoot("t_root");
	}

	void loadStuff()
	{
		Jam::Texture metal;
		metal.path = "texture/metal.png";
		metal.minFilter = GL_LINEAR;
		metal.magFilter = GL_LINEAR;

		Jam::GFXLibrary::registerTexture("metal", metal);

		Jam::RenderEngine::preloadTexture("metal");

		Jam::Texture mario;
		mario.path = "texture/mario.png";
		mario.minFilter = GL_LINEAR;
		mario.magFilter = GL_LINEAR;

		Jam::GFXLibrary::registerTexture("mario", mario);

		Jam::RenderEngine::preloadTexture("mario");

		Jam::RenderEngine::load();

		while (Jam::RenderEngine::remainingLoadEntries() > 0);
	}

	void update(double delta)
	{
		
	}

	void exit()
	{
		removeRoot("TestRoot");
		delete root;
	}

private:
	Jam::Root* root = nullptr;
	Jam::Box2DListener _listener;
	b2World* _world;
};