#include "guibutton.h"

Jam::GUIButton::GUIButton(RenderEngine * engine, int layer, float anchorX, float anchorY, 
	std::string texture, b2Shape * shape)
	: GUIInput(engine, layer, anchorX, anchorY, texture, shape) {}

Jam::GUIButton::~GUIButton() {}

void Jam::GUIButton::_init() {
	GUIElement::_init();
}

bool Jam::GUIButton::isDown() {
	return _isDown;
}

void Jam::GUIButton::_highlight() {}

void Jam::GUIButton::_dehighlight() {}

void Jam::GUIButton::_down() {
	_isDown = true;
}

void Jam::GUIButton::_up() {
	_isDown = false;
}
