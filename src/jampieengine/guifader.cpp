#include "guifader.h"
#include "renderengine.h"
#include "entity.h"

using namespace Jam;

Jam::GUIFader::GUIFader(RenderEngine * engine, int layer, float anchorX, float anchorY, 
						std::string on, std::string off, std::string value):
	GUIElement(engine, layer, anchorX, anchorY, on) {
	_materialOff.texture = off;
	_materialValue.texture = value;
	_isFader = true;
}

Jam::GUIFader::~GUIFader() {}

float Jam::GUIFader::getValue() {
	return _value;
}

void Jam::GUIFader::setValue(float value) {
	_value = value;
}

void Jam::GUIFader::draw() {
	if (!isActive())
		return;

	while (!_shouldDraw);

	switch (GRAPHICS_TYPE) {
		case GRAPHICS_TYPE_OPENGL:
			//Bind shader program
			_glRenderer->getShaderProgram()->bind();

			_glRenderer->getShaderProgram()->sendUniformMat4f("model",
								_calculateTransform().getMatrix());

			//Bind material
			_glRenderer->getShaderProgram()->sendUniform4f("color", 1.0, 1.0, 1.0, 1.0);
			_glRenderer->getShaderProgram()->sendUniform1i("texture", 0);
			GLLibrary::getTexture(_material.texture)->bind(0);

			//Since it is a fader
			_glRenderer->getShaderProgram()->sendUniform1i("textureOff", 1);
			GLLibrary::getTexture(_materialOff.texture)->bind(1);
			_glRenderer->getShaderProgram()->sendUniform1i("valueTexture", 2);
			GLLibrary::getTexture(_materialValue.texture)->bind(2);

			//It is a fader
			_glRenderer->getShaderProgram()->sendUniform1i("isFader", _isFader);

			_glRenderer->getShaderProgram()->sendUniform1f("value", _value);

			//Draw the basterd
			_glRenderer->getMesh()->draw();
			break;
	}

	_shouldDraw = false;
}
