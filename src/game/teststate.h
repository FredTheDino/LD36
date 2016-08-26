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
#include "animation.h"

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
		
		Jam::AnimationMachine* animation = new Jam::AnimationMachine();
		entity->add(animation);

		
		Jam::Animation a_red;
		a_red.spriteSheet = "fire_ball";
		a_red.speed = 20;
		a_red.frames = {
			{ 0, 0 },
			{ 1, 0 },
			{ 2, 0 },
			{ 3, 0 },
			{ 4, 0 },
			{ 5, 0 }
		};

		Jam::Animation a_blue;
		a_blue.spriteSheet = "fire_ball";
		a_blue.speed = 20;
		a_blue.frames = {
			{ 0, 1 },
			{ 1, 1 },
			{ 2, 1 },
			{ 3, 1 },
			{ 4, 1 },
			{ 5, 1 }
		};


		animation->addAnimation("red", a_red);
		animation->addAnimation("blue", a_blue);

		//Root adding
		
		root->addNode(0, "fire_ball", (Jam::Node*) entity);

		addRoot("t_root", root);
		enterRoot("t_root");

		//Keys
		Jam::InputHandler::registerInput("switch", Jam::InputBinding(true, SDLK_g));
	}

	void update(double delta)
	{
		if (Jam::InputHandler::keyPressed("switch"))
			_gameStateManager->enterState("test2");
	}

	void exit()
	{
		Jam::RenderEngine::unloadSpriteSheet("fire_ball");
	}

private:
	
};

class TestState2 : Jam::GameState
{
public:

	void init()
	{
		Jam::Root* root = new Jam::Root();

		//Texture

		Jam::RenderEngine::preloadTexture("mario");

		Jam::RenderEngine::load();

		while (Jam::RenderEngine::remainingLoadEntries() > 0);

		//Entity
		Jam::Entity* mario = new Jam::Entity();

		Jam::Material m_mario;
		m_mario.texture = "mario";

		mario->add(new Jam::Renderer(getRenderEngine(), 0, "quad", m_mario));

		root->addNode(0, "mario", (Jam::Node*) mario);

		addRoot("test", root);

		enterRoot("test");

		//Keys
		Jam::InputHandler::registerInput("switch", Jam::InputBinding(true, SDLK_g));
	}

	void update(double delta)
	{
		if (Jam::InputHandler::keyPressed("switch"))
			_gameStateManager->enterState("test1");
	}

	void exit()
	{
		Jam::RenderEngine::unloadTexture("mario");
	}

private:
	
};