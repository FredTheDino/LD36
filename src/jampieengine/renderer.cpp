#include "renderer.h"
#include "entity.h"

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
		//Bind shader program
		_glRenderer->_shaderProgram->bind();

		//Send matrices
		_glRenderer->_shaderProgram->sendUniformMat4f("projection", _renderEngine->getCamera()->getProjection());
		_glRenderer->_shaderProgram->sendUniformMat4f("view", _renderEngine->getCamera()->getView());
		_glRenderer->_shaderProgram->sendUniformMat4f("model", getParent()->getTransformationMatrix());

		//Bind material
		GLLibrary::getTexture(_material.texture)->bind();
		_glRenderer->_shaderProgram->sendUniform4f("color", _material.baseColor.x, _material.baseColor.y, _material.baseColor.z, _material.baseColor.w);

		_glRenderer->_mesh->draw();
		break;
	}

	_shouldDraw = false;
}

void Jam::Renderer::setShaderProgram(std::string tag) {
	switch (GRAPHICS_TYPE) {
		case GRAPHICS_TYPE_OPENGL:
			_glRenderer->setShaderProgram(GLLibrary::getShaderProgram(tag));
	}
}

void Renderer::setMesh(std::string tag)
{
	switch (GRAPHICS_TYPE) {
	case GRAPHICS_TYPE_OPENGL:
		_glRenderer->setMesh(GLLibrary::getMesh(tag));
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