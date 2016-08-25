#include "gui.h"
#include "entity.h"
#include "glm/glm.hpp"
#include "material.h"
#include "transform.h"

Jam::GUIElement::GUIElement(RenderEngine* engine, int layer, float anchorX, float anchorY, std::string texture):
	Renderer(engine, layer, "quad", texture) {
		setAnchor(anchorX, anchorY);
		
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

			_glRenderer->getShaderProgram()->sendUniformMat4f("model", 
															  _calculateTransform().getMatrix());

			//Send shader data
			//_glRenderer->getShaderProgram()->sendUniform2i("screen", w, h);
			_glRenderer->getShaderProgram()->sendUniform1i("isFader", _isFader);
			

			//Bind material
			GLLibrary::getTexture(_material.texture)->bind(0);
			_glRenderer->getShaderProgram()->sendUniform1i("texture", 0);
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

Jam::Transform Jam::GUIElement::_calculateTransform() {
	int w, h;
	_renderEngine->getWindow().getSize(&w, &h);

	//Send transform
	Transform t = getParent()->getTransform();

	t.position.x /= w;
	t.position.y /= h;

	t.position.x += 0.5;
	t.position.y += 0.5;

	t.translate(_anchor[0], _anchor[1]);

	t.scale.x /= 0.5 * w;
	t.scale.y /= 0.5 * h;

	return t;
}
