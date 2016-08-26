#pragma once

#include "pie.h"

#include "gamestate.h"
#include "gamestatelibrary.h"
#include "root.h"
#include "entity.h"
#include "node.h"
#include "component.h"
#include "camera.h"
#include "audiohandler.h"
#include "soundsource.h"
#include "audiocomponenttest.h"
#include "renderer.h"
#include "guibutton.h"

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

void onDown(Jam::GUIInput* component) {
	std::cout << "Something pressed this! :D" << std::endl;
}

void onHover(Jam::GUIInput* component) {
	component->setTexture("on");
}

void offHover(Jam::GUIInput* component) {
	component->setTexture("off");
}

class TestState: Jam::GameState
{
public:


	void init()
	{
		loadStuff();

		Jam::Entity* dummy = new Jam::Entity();

		Jam::Entity* gui = new Jam::Entity();

		Jam::Material mat;
		mat.texture = "mario";
		mat.baseColor = glm::vec4(1.0, 1.0, 1.0, 1.0);
		dummy->add(new Jam::Renderer(getRenderEngine(), 0, "quad", mat));


		gui->scale(300, 100);
		b2PolygonShape shape;
		shape.SetAsBox(150, 50);
		//gui->add(new Jam::GUIFader(getRenderEngine(), 10, 0, 0, "on", "off", "map"));
		gui->add(new Jam::GUIButton(getRenderEngine(), 10, 0, 1, "on", &shape));
		//gui->add(new Jam::GUIButton(getRenderEngine(), 10, 0, 0, "on", &shape));

		//gui->add(new AudioComponentTest());

		///*
		gui->get<Jam::GUIButton>()->setOnPress(onDown);
		gui->get<Jam::GUIButton>()->setOnHighlight(onHover);
		gui->get<Jam::GUIButton>()->setOnDehighlight(offHover);
		//*/

		Jam::Root* root = new Jam::Root();

		root->addNode(0, "dummy", (Jam::Node*) dummy);
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

		//slider test stuff
		Jam::Texture on;
		on.path = "slidertest/on.png";
		on.minFilter = Jam::TEX_PARAM_LINEAR;
		on.magFilter = Jam::TEX_PARAM_LINEAR;
		on.wrapS = Jam::TEX_PARAM_CLAMP;
		on.wrapT = Jam::TEX_PARAM_CLAMP;

		Jam::GFXLibrary::registerTexture("on", on);
		Jam::RenderEngine::preloadTexture("on");
		
		Jam::Texture off;
		off.path = "slidertest/off.png";
		off.minFilter = Jam::TEX_PARAM_LINEAR;
		off.magFilter = Jam::TEX_PARAM_LINEAR;
		off.wrapS = Jam::TEX_PARAM_CLAMP;
		off.wrapT = Jam::TEX_PARAM_CLAMP;

		Jam::GFXLibrary::registerTexture("off", off);
		Jam::RenderEngine::preloadTexture("off");

		Jam::Texture map;
		map.path = "slidertest/map.png";
		map.minFilter = Jam::TEX_PARAM_LINEAR;
		map.magFilter = Jam::TEX_PARAM_LINEAR;
		map.wrapS = Jam::TEX_PARAM_CLAMP;
		map.wrapT = Jam::TEX_PARAM_CLAMP;

		Jam::GFXLibrary::registerTexture("map", map);

		Jam::RenderEngine::preloadTexture("map");


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
		if (Jam::InputHandler::keyDown("switch_root")) {
			//enterRoot("up_test");
			getRenderEngine()->getCamera()->transform.position.y += delta * 2;
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