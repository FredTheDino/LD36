#include "guislider.h"

#include <algorithm> 

Jam::GUISlider::GUISlider(RenderEngine * engine, int layer, float anchorX, float anchorY, 
						  std::string on, std::string off, std::string value, 
						  b2Shape * shape): GUIInput(engine, layer, anchorX, anchorY, on, shape)
{
	_materialOff.texture = off;
	_materialValue.texture = value;
	setShape(shape);
	_isFader = true;
}

Jam::GUISlider::~GUISlider() {}

void Jam::GUISlider::setValue(float value) {
	_value = value;
}

float Jam::GUISlider::getValue() {
	return _value;
}

void Jam::GUISlider::setShape(b2Shape* shape) {
	b2AABB aabb;
	shape->ComputeAABB(&aabb, Transform(), 0);
	_minXOffset = aabb.lowerBound.x;
	_invertedWidth = 1.0 / (aabb.upperBound.x - _minXOffset);

	GUIInput::setShape(shape);
}

void Jam::GUISlider::_update(double delta) {
	GUIInput::_update(delta);
	if (_isHeld) {
		_computeSliderPosition();
	}
}

void Jam::GUISlider::draw() {
	if (!isActive())
		return;

	while (!_shouldDraw && !RenderEngine::shouldLoad());

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

void Jam::GUISlider::_highlight() {}

void Jam::GUISlider::_dehighlight() {}

void Jam::GUISlider::_down() {
	_isHeld = true;
	_computeSliderPosition();
}

void Jam::GUISlider::_up() {
	_isHeld = false;
}

void Jam::GUISlider::_computeSliderPosition() {
	int w, h;
	_renderEngine->getWindow().getSize(&w, &h);

	float xPos = _calculateTransform().position.x;
	_value = InputHandler::getMousePos().x - (_minXOffset + xPos * w);
	
	_value *= _invertedWidth;

	_value = (_value < 1) ? _value : 1;
	_value = (0 < _value) ? _value : 0;
}
