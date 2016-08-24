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
#include "sst.h"

void col(b2Contact* contact) {
	std::cout << "y: " << contact->GetFixtureA()->GetBody()->GetTransform().p.y << std::endl;
}

class TestState: Jam::GameState
{
public:

	void init()
	{
		//Save

		std::cout << "SAVES===========" << std::endl;

		Jam::SST save;

		save.add("str_test", "This is a string!");
		save.add("int_test", 1337);
		save.add("short_test", (short) 420);
		save.add("char_test", (char) 69);

		Jam::Loader::saveSST(save, "save/test.sst");

		Jam::SST load = Jam::Loader::loadSST("save/test.sst");

		short v_short;
		load.get("short_test", v_short);

		std::string str;

		load.get("str_test", str);

		std::cout << "SAVES===========" << std::endl;

		loadStuff();

		//Root 1

		Jam::Root* root = new Jam::Root();

		Jam::Entity* entity = new Jam::Entity();
		entity->add(new TestComponent(getRenderEngine()->getCamera()));

		Jam::Material material;
		material.texture = "metal";

		entity->add(new Jam::Renderer(getRenderEngine(), 0, "quad", material));
		entity->add(new AudioComponentTest());

		root->addNode(0, "t_metal", (Jam::Node*) entity);

		Jam::Entity* mario = new Jam::Entity();
		mario->add(new TestComponent(getRenderEngine()->getCamera()));
		
		Jam::Material material_mario;
		material_mario.texture = "mario";

		mario->add(new Jam::Renderer(getRenderEngine(), 1, "quad", material_mario));

		root->addNode(0, "t_mario", (Jam::Node*) mario);

		mario->transform.translateX(.5f);

		addRoot("t_root", root);

		//Root 2

		Jam::Root* root2 = new Jam::Root();

		Jam::Entity* entity_up_test = new Jam::Entity();

		Jam::Material material_up_test;
		material_up_test.texture = "up_test";

		entity_up_test->add(new Jam::Renderer(getRenderEngine(), 0, "quad", material_up_test));

		root2->addNode(0, "up_test", (Jam::Node*) entity_up_test);

		addRoot("up_test", root2);

		enterRoot("t_root");

		//Keys
		Jam::InputHandler::registerInput("switch_root", Jam::InputBinding(true, SDLK_p));
	}

	void loadStuff()
	{
		//Metal
		
		Jam::Texture metal;
		metal.path = "texture/metal.png";
		metal.minFilter = Jam::TEX_PARAM_LINEAR;
		metal.magFilter = Jam::TEX_PARAM_LINEAR;

		Jam::GFXLibrary::registerTexture("metal", metal);

		Jam::RenderEngine::preloadTexture("metal");

		//Mario

		Jam::Texture mario;
		mario.path = "texture/mario.png";
		mario.minFilter = Jam::TEX_PARAM_LINEAR;
		mario.magFilter = Jam::TEX_PARAM_LINEAR;

		Jam::GFXLibrary::registerTexture("mario", mario);

		Jam::RenderEngine::preloadTexture("mario");

		//Up Test

		Jam::Texture up_test;
		up_test.path = "texture/up_test.png";
		up_test.minFilter = Jam::TEX_PARAM_NEAREST;
		up_test.magFilter = Jam::TEX_PARAM_NEAREST;

		Jam::GFXLibrary::registerTexture("up_test", up_test);

		Jam::RenderEngine::preloadTexture("up_test");

		Jam::RenderEngine::load();

		while (Jam::RenderEngine::remainingLoadEntries() > 0);
	}

	void update(double delta)
	{
		if (Jam::InputHandler::keyPressed("switch_root")) {
			enterRoot("up_test");
		}
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