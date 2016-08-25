#include "glrenderer.h"
#include "entity.h"

using namespace Jam;

GLRenderer::GLRenderer(Renderer& renderer, std::string mesh, std::string shaderProgram, Material& material)
	: _renderer(renderer), _material(material)
{
	_setMesh(GLLibrary::getMesh(mesh));
	_setShaderProgram(GLLibrary::getShaderProgram(shaderProgram));
	
	if (material.spriteSheet) {
		_setTexture(GLLibrary::getSpriteSheet(material.texture)->getTexture(material.ssOffsetX, material.ssOffsetY));
	}
	else {
		_setTexture(GLLibrary::getTexture(material.texture));
	}
}

void GLRenderer::draw()
{
	//Bind shader program
	_shaderProgram->bind();
	
	//Send matrices
	_shaderProgram->sendUniformMat4f("projection", _renderer._renderEngine->getCamera()->getProjection());
	_shaderProgram->sendUniformMat4f("view", _renderer._renderEngine->getCamera()->getView());
	_shaderProgram->sendUniformMat4f("model", _renderer.getParent()->transform.getMatrix());

	//Bind material
	
	_texture->bind();

	_shaderProgram->sendUniform4f("color", _material.baseColor.x, _material.baseColor.y, _material.baseColor.z, _material.baseColor.w);

	_mesh->draw();
}

void GLRenderer::_setMesh(GLMesh* mesh)
{
	_mesh = mesh;
}

void GLRenderer::_setShaderProgram(GLShaderProgram* shaderProgram)
{
	_shaderProgram = shaderProgram;
}

void GLRenderer::_setTexture(GLTexture* texture)
{
	_texture = texture;
}