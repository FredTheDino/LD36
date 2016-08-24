#include "guifader.h"
#include "renderengine.h"
#include "entity.h"

using namespace Jam;

Jam::GUIFader::GUIFader(RenderEngine * engine, int layer, float anchorX, float anchorY, 
						Material off, Material on, Material value): 
	GUIElement(engine, layer, anchorX, anchorY, on) {
	_materialOff = off;
	_materialValue = value;
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

			//Send transform
			_glRenderer->getShaderProgram()->sendUniformMat4f("model", getParent()->getTransformationMatrix());

			//Send shader data
			int w, h;
			_renderEngine->getWindow().getSize(&w, &h);
			_glRenderer->getShaderProgram()->sendUniform2i("screen", w, h);
			_glRenderer->getShaderProgram()->sendUniform2f("anchor", _anchor[0], _anchor[1]);
			_glRenderer->getShaderProgram()->sendUniform1i("isFader", _isFader);

			//Since it is a fader
			_glRenderer->getShaderProgram()->sendUniform1f("value", _value);
			GLLibrary::getTexture(_materialOff.texture)->bind();
			GLLibrary::getTexture(_materialValue.texture)->bind();

			//Bind material
			GLLibrary::getTexture(_material.texture)->bind();
			_glRenderer->getShaderProgram()->sendUniform4f("color", _material.baseColor.x, _material.baseColor.y, _material.baseColor.z, _material.baseColor.w);

			//Draw the basterd
			_glRenderer->getMesh()->draw();
			break;
	}

	_shouldDraw = false;
}
