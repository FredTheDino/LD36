#include "guiinput.h"

namespace Jam {



	GUIInput::GUIInput(RenderEngine * engine, int layer, float anchorX, float anchorY, 
					   std::string texture, b2Shape* shape): 
		GUIElement(engine, layer, anchorX, anchorY, texture) {
		setShape(shape);
	}

	GUIInput::~GUIInput() {
		delete _shape;
	}

	void GUIInput::setOnHighlight(void(*func)(GUIInput*)) {
		_onHighlight = func;
	}

	void GUIInput::setOnDehighlight(void(*func)(GUIInput*)) {
		_onDehighlight = func;
	}

	void GUIInput::setOnPress(void(*func)(GUIInput*)) {
		_onPress = func;
	}

	void GUIInput::setOnRelease(void(*func)(GUIInput*)) {
		_onRelease = func;
	}

	void GUIInput::_update(double delta) {
		
		int w, h;
		_renderEngine->getWindow().getSize(&w, &h);

		Transform t = _calculateTransform();

		t.position.x *= w;
		t.position.y = (1 - t.position.y) * h;

		glm::vec2 mousePos = InputHandler::getMousePos();
		b2Vec2 b2MousePos;
		b2MousePos.x = (float32) mousePos.x;
		b2MousePos.y = (float32) mousePos.y;

		if (_shape->TestPoint((b2Transform) t, b2MousePos)) {
			if (!_hoverd) {
				_hoverd = true;
				_highlight();
				if (_onHighlight)
					_onHighlight(this);
			}

			if (InputHandler::keyPressed("ui_select")) {
				_down();
				if (_onPress)
					_onPress(this);
			}
		} else {
			if (_hoverd) {
				_hoverd = false;
				_dehighlight();
				if (_onDehighlight)
					_onDehighlight(this);
			}
		}

		if (InputHandler::keyReleased("ui_select")) {
			_up();
			if (_onRelease)
				_onRelease(this);
		}
	}

	void GUIInput::setShape(b2Shape* shape) {
		if (_shape) {
			delete _shape;
		}

		switch (shape->GetType()) {
			case b2Shape::Type::e_circle:
			{
				b2CircleShape s = *((b2CircleShape*) shape);
				_shape = new b2CircleShape(s);
				break;
			}
			case b2Shape::Type::e_edge:
			{
				b2EdgeShape s = *((b2EdgeShape*) shape);
				_shape = new b2EdgeShape(s);
				break;
			}
			case b2Shape::Type::e_polygon:
			{
				b2PolygonShape s = *((b2PolygonShape*) shape);
				_shape = new b2PolygonShape(s);
				break;
			}
			case b2Shape::Type::e_chain:
			{
				b2ChainShape s = *((b2ChainShape*) shape);
				_shape = new b2ChainShape(s);
				break;
			}
			default:
				break;
		}
	}

}