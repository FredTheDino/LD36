#include "trapcomponent.h"
#include "entity.h"
#include "inputhandler.h"
#include "Box2D/Box2D.h"
#include "glm/glm.hpp"

using namespace Jam;


TrapComponent::TrapComponent(Jam::RenderEngine* engine, Jam::Material material, std::string trigger, float coolDown, float fireTime, glm::vec2 min, glm::vec2 max): Jam::Component() {
	_engine = engine;
	_coolDown = coolDown;
	_fireTime = fireTime;
	_t = _fireTime;
	_material = material;
	_trigger = trigger;
	_min = min;
	_max = max;
}

TrapComponent::~TrapComponent() {}

void TrapComponent::_init() {
	getParent()->add(new Jam::Renderer(_engine, 100, "quad", _material));
}

void TrapComponent::_update(double delta) {
	/*
	if (Jam::InputHandler::keyPressed("fire_spike")) {
		std::cout << "CLICK!" << std::endl;

		int w, h;
		_engine->getWindow().getSize(&w, &h);

		glm::vec2 mousePos = Jam::InputHandler::getMousePos();

		glm::vec4 mouse;

		mouse.x = (mousePos.x / w - 0.5) * 2;
		mouse.y = (mousePos.y / h - 0.5) * 2;

		//Jam::Transform t = getParent()->getTransform();
		//mouse = mouse * t.getMatrix();
		mouse = mouse * _engine->getCamera()->orthographic(-1 * (float) h / (float) w, 1 * (float) h / (float) w, -1, 1);
		//mouse = mouse + glm::vec4(-_engine->getCamera()->transform.position.x + t.position.x, _engine->getCamera()->transform.position.y - t.position.y, 0.0, 0.0);
		
		

		if (_min.x < mouse.x && _min.y < mouse.y) {
			if (mouse.x < _max.x && mouse.y < _max.y) {
				_fire();
			}
		}
	}
	*/
	_t += delta;
	if (_isFireing) {
		if (_fireTime <= _t) {
			_isFireing = false;
			_t = 0;
			_reset();
		}
	} else {
		if (InputHandler::keyPressed(_trigger)) {
			if (_coolDown <= _t) {
				_isFireing = true;
				_t = 0;
				_fire();
			}
		}
	}
}

void TrapComponent::_end() {}

void TrapComponent::_rootEnter() {}

void TrapComponent::_rootExit() {}
