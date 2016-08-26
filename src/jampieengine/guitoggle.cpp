#include "guitoggle.h"

Jam::GUIToggle::GUIToggle(RenderEngine * engine, int layer, float anchorX, float anchorY, std::string on, std::string off, b2Shape * shape): 
	GUIButton(engine, layer, anchorX, anchorY, off, shape) {
	_isDown = false;
	_texOn = on;
	_texOff = off;
}

Jam::GUIToggle::~GUIToggle() {}

void Jam::GUIToggle::_highlight() {}

void Jam::GUIToggle::_dehighlight() {}

void Jam::GUIToggle::_down() {
	_isDown = !_isDown;
	setTexture(_isDown ? _texOn : _texOff);
}

void Jam::GUIToggle::_up() {}