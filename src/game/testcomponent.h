#pragma once

#include <SDL2/SDL.h>
#include "loader.h"

#include "gamestate.h"
#include "gamestatelibrary.h"
#include "root.h"
#include "entity.h"
#include "node.h"
#include "component.h"
#include "audiohandler.h"
#include "audiolibrary.h"
#include "soundsource.h"
#include "audiolistener.h"
#include "camera.h"
#include "renderer.h"

class TestComponent : public Jam::Component {
public:
	TestComponent(Jam::Camera* camera)
		: _camera(camera)
	{

	}

	void _rootEnter() {};

	void _init() {
		Jam::InputHandler::registerInput("left", Jam::InputBinding(true, SDLK_LEFT));
		Jam::InputHandler::registerInput("right", Jam::InputBinding(true, SDLK_RIGHT));
		Jam::InputHandler::registerInput("up", Jam::InputBinding(true, SDLK_UP));
		Jam::InputHandler::registerInput("down", Jam::InputBinding(true, SDLK_DOWN));
	}

	void _update(double delta) {
		if (Jam::InputHandler::keyDown("left"))
			_camera->transform.translateX(-delta);
		if (Jam::InputHandler::keyDown("right"))
			_camera->transform.translateX(delta);
		if (Jam::InputHandler::keyDown("up"))
			_camera->transform.translateY(delta);
		if (Jam::InputHandler::keyDown("down"))
			_camera->transform.translateY(-delta);

		getParent()->transform.rotateZ(delta);
	}

	void _end() {

	}

	void _rootExit() {};

	void reset() {
		i = 0;
	}

private:
	int i;

	Jam::Camera* _camera;

};