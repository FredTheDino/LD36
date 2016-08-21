#include "glrenderer.h"

using namespace Jam;

GLRenderer::GLRenderer(Renderer& renderer, std::string mesh, std::string shaderProgram)
	: _renderer(renderer)
{
	_setMesh(GLLibrary::getMesh(mesh));
	_setShaderProgram(GLLibrary::getShaderProgram(shaderProgram));
}

void GLRenderer::draw()
{
	_shaderProgram->bind();
	_shaderProgram->sendUniformMat4f("transform", _renderer.getParent()->transform.getMatrix());
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