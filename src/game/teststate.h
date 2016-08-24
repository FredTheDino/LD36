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
#include "gui.h"

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
		loadStuff();

		Jam::Entity* gui = new Jam::Entity();

		Jam::Material material;
		material.texture = "up_test";

		gui->add(new Jam::GUIElement(getRenderEngine(), 10, 0, 0, material));

		Jam::Root* root = new Jam::Root();

		root->addNode(0, "gui", (Jam::Node*) gui);

		addRoot("gui", root);

		enterRoot("gui");

		//Keys
		Jam::InputHandler::registerInput("switch_root", Jam::InputBinding(true, SDLK_p));
	}

	void loadStuff()
	{
		//YAY COpY PASTE
		Jam::ShaderProgram shaderProgram;

		shaderProgram.vertexShader = Jam::Loader::loadText("shader/GUIShader.vert");
		shaderProgram.fragmentShader = Jam::Loader::loadText("shader/GUIShader.frag");

		Jam::GFXLibrary::registerShaderProgram("GUIShader", shaderProgram);

		Jam::RenderEngine::preloadShaderProgram("GUIShader");

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