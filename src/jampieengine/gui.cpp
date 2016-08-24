#include "gui.h"

Jam::GUI::GUI(RenderEngine* engine, int layer, Material material, float anchorX, float anchorY):
	Renderer(engine, layer, "quad", material), _anchor(anchorX, anchorY) {
	setShaderProgram("gui_super_shader");
}

Jam::GUI::~GUI() {}

void Jam::GUI::draw() {

}

void Jam::GUI::setAnchor(glm::vec2 anchor) {
	_anchor = anchor;

}

void Jam::GUI::setAnchor(float x, float y) {
	_anchor = glm::vec2(x, y);
}

glm::vec2 Jam::GUI::getAnchor() {
	return _anchor;
}
