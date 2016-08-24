#include "gui.h"
#include "entity.h"

Jam::GUIElement::GUIElement(RenderEngine* engine, int layer, float anchorX, float anchorY, Material material):
	Renderer(engine, layer, "quad", material), _anchor(anchorX, anchorY) {
}

Jam::GUIElement::~GUIElement() {}

void Jam::GUIElement::_init() {
	Renderer::_init();
	setShaderProgram("GUIShader");
}

void Jam::GUIElement::draw() {
	if (!isActive())
		return;

	while (!_shouldDraw);

	switch (GRAPHICS_TYPE) {
		case GRAPHICS_TYPE_OPENGL:
			//Bind shader program
			_glRenderer->getShaderProgram()->bind();

			//Send transform
			_glRenderer->getShaderProgram()->sendUniformMat4f("model", getParent()->getTransformationMatrix());
			
			//Send shader data
			int w, h;
			_renderEngine->getWindow().getSize(&w, &h);
			_glRenderer->getShaderProgram()->sendUniform2i("screen", w, h);
			_glRenderer->getShaderProgram()->sendUniform2f("anchor", _anchor[0], _anchor[1]);
			_glRenderer->getShaderProgram()->sendUniform1i("isFader", _isFader);
			
			//Bind material
			GLLibrary::getTexture(_material.texture)->bind();
			_glRenderer->getShaderProgram()->sendUniform4f("color", _material.baseColor.x, _material.baseColor.y, _material.baseColor.z, _material.baseColor.w);

			//Draw the basterd
			_glRenderer->getMesh()->draw();
			break;
	}

	_shouldDraw = false;
}

void Jam::GUIElement::setAnchor(glm::vec2 anchor) {
	_anchor = anchor;
}

void Jam::GUIElement::setAnchor(float x, float y) {
	_anchor = glm::vec2(x, y);
}

glm::vec2 Jam::GUIElement::getAnchor() {
	return _anchor;
}
