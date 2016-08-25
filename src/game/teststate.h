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
#include "spritesheet.h"

void col(b2Contact* contact) {
	std::cout << "y: " << contact->GetFixtureA()->GetBody()->GetTransform().p.y << std::endl;
}

class TestState: Jam::GameState
{
public:

	void init()
	{
		Jam::Root* root = new Jam::Root();

		//Sprite sheet

		Jam::SpriteSheet ss;
		ss.path = "texture/fire_ball.png";
		ss.tilesX = 6;
		ss.tilesY = 2;

		Jam::GFXLibrary::registerSpriteSheet("fire_ball", ss);

		Jam::RenderEngine::preloadSpriteSheet("fire_ball");

		Jam::RenderEngine::load();

		while (Jam::RenderEngine::remainingLoadEntries() > 0);

		//Entity

		Jam::Entity* entity = new Jam::Entity();
		
		Jam::Material material;
		material.texture = "fire_ball";
		material.spriteSheet = true;
		material.ssOffsetX = 0;
		material.ssOffsetY = 0;

		entity->add(new Jam::Renderer(getRenderEngine(), 0, "quad", material));
		
		root->addNode(0, "fire_ball", (Jam::Node*) entity);

		addRoot("t_root", root);
		enterRoot("t_root");

		//Keys
		Jam::InputHandler::registerInput("blue", Jam::InputBinding(true, SDLK_k));
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
		static int blue = 0;

		if (Jam::InputHandler::keyPressed("blue")) {
			if (blue == 0)
				blue = 1;
			else
				blue = 0;
		}

		static float d;
		d += delta;
		if (d >= .05f) {
			static int i;

			((Jam::Entity*) getCurrentRoot()->getNode("fire_ball"))->get<Jam::Renderer>()->setTexture("fire_ball", i % 6, blue);

			i++;

			d = 0;
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