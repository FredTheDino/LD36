#include "glrenderer.h"

using namespace Jam;

GLRenderer::GLRenderer(std::string mesh, std::string shaderProgram)
{
	_setMesh(GLLibrary::getMesh(mesh));
	_setShaderProgram(GLLibrary::getShaderProgram(shaderProgram));
}

void GLRenderer::draw()
{
	_shaderProgram->bind();
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