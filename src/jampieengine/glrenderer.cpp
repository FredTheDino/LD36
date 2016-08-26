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