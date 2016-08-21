#include "renderer.h"

using namespace Jam;

Renderer::Renderer(RenderEngine* renderEngine, std::string mesh)
	: GRAPHICS_TYPE(renderEngine->GRAPHICS_TYPE), _renderEngine(renderEngine)
{
	switch (GRAPHICS_TYPE) {
	case GRAPHICS_TYPE_OPENGL:
		_glRenderer = new GLRenderer(*this, mesh, GFXLibrary::getMesh(mesh).shaderProgram);
		break;
	}
}

void Renderer::_begin()
{
	_renderEngine->addRenderer(0, this);
}

void Renderer::draw()
{
	if (!isActive())
		return;

	switch (GRAPHICS_TYPE) {
	case GRAPHICS_TYPE_OPENGL:
		_glRenderer->draw();
		break;
	}
}

void Renderer::setMesh(std::string tag)
{
	switch (GRAPHICS_TYPE) {
	case GRAPHICS_TYPE_OPENGL:
		_glRenderer->_setMesh(GLLibrary::getMesh(tag));
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