#include "renderer.h"

using namespace Jam;

Renderer::Renderer(RenderEngine* renderEngine, int priority, std::string mesh, Material material, std::string shaderProgram)
	: GRAPHICS_TYPE(renderEngine->GRAPHICS_TYPE), _renderEngine(renderEngine), _priority(priority), _mesh(mesh),
		_material(material)
{
	_shaderProgram = (shaderProgram.length() == 0 ? GFXLibrary::getMesh(_mesh).shaderProgram : shaderProgram);
}

void Renderer::_rootEnter()
{
	_associationID = _renderEngine->addRenderer(_priority, this);
}

void Renderer::_init()
{
	switch (GRAPHICS_TYPE) {
	case GRAPHICS_TYPE_OPENGL:
		_glRenderer = new GLRenderer(*this, _mesh, _shaderProgram, _material);
		break;
	}
}

void Renderer::_rootExit()
{
	_renderEngine->removeRenderer(_associationID);
	_renderEngine->cancelRendering();
}

void Renderer::draw()
{
	if (!isActive())
		return;

	while (!_shouldDraw);

	switch (GRAPHICS_TYPE) {
	case GRAPHICS_TYPE_OPENGL:
		_glRenderer->draw();
		break;
	}

	_shouldDraw = false;
}

void Renderer::setMesh(std::string tag)
{
	switch (GRAPHICS_TYPE) {
	case GRAPHICS_TYPE_OPENGL:
		_glRenderer->_setMesh(GLLibrary::getMesh(tag));
		break;
	}
}

void Renderer::setShaderProgram(std::string tag)
{
	switch (GRAPHICS_TYPE) {
	case GRAPHICS_TYPE_OPENGL:
		_glRenderer->_setShaderProgram(GLLibrary::getShaderProgram(tag));
		break;
	}
}

Renderer::~Renderer()
{
	switch (GRAPHICS_TYPE) {
	case GRAPHICS_TYPE_OPENGL:
		delete _glRenderer;
		break;
	}
}