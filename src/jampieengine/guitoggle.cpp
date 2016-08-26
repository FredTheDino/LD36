#include "guitoggle.h"

Jam::GUIToggle::GUIToggle(RenderEngine * engine, int layer, float anchorX, float anchorY, std::string on, std::string off, b2Shape * shape): 
	GUIButton(engine, layer, anchorX, anchorY, off, shape) {
	_isDown = false;
	_on.texture = on;
	_off.texture = off;
}

Jam::GUIToggle::~GUIToggle() {}

void Jam::GUIToggle::_highlight() {}

void Jam::GUIToggle::_dehighlight() {}

void Jam::GUIToggle::_down() {
	_isDown = !_isDown;
	setMaterial(_isDown ? _on : _off);
}

void Jam::GUIToggle::_up() {}
