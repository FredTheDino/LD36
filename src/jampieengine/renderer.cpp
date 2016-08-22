#include "renderer.h"

using namespace Jam;

Renderer::Renderer(RenderEngine* renderEngine, std::string mesh, Material material)
	: GRAPHICS_TYPE(renderEngine->GRAPHICS_TYPE), _renderEngine(renderEngine), _mesh(mesh), _material(material)
{
	
}

void Renderer::_rootEnter()
{
	_associationID = _renderEngine->addRenderer(0, this);
}

void Renderer::_init()
{
	switch (GRAPHICS_TYPE) {
	case GRAPHICS_TYPE_OPENGL:
		_glRenderer = new GLRenderer(*this, _mesh, GFXLibrary::getMesh(_mesh).shaderProgram, _material);
		break;
	}
}

void Renderer::_rootExit()
{
	_renderEngine->removeRenderer(_associationID);
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

Renderer::~Renderer()
{
	switch (GRAPHICS_TYPE) {
	case GRAPHICS_TYPE_OPENGL:
		delete _glRenderer;
		break;
	}
}