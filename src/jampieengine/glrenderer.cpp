#include "glrenderer.h"
#include "entity.h"

using namespace Jam;

GLRenderer::GLRenderer(Renderer& renderer, std::string mesh, std::string shaderProgram, Material& material)
	: _renderer(renderer), _material(material)
{
	setMesh(GLLibrary::getMesh(mesh));
	setShaderProgram(GLLibrary::getShaderProgram(shaderProgram));
}

void GLRenderer::draw()
{
	//Bind shader program
	_shaderProgram->bind();
	
	//Send matrices
	_shaderProgram->sendUniformMat4f("projection", _renderer._renderEngine->getCamera()->getProjection());
	_shaderProgram->sendUniformMat4f("view", _renderer._renderEngine->getCamera()->getView());
	_shaderProgram->sendUniformMat4f("model", _renderer.getParent()->getTransformationMatrix());

	//Bind material
	GLLibrary::getTexture(_material.texture)->bind();
	_shaderProgram->sendUniform4f("color", _material.baseColor.x, _material.baseColor.y, _material.baseColor.z, _material.baseColor.w);

	_mesh->draw();
}

void GLRenderer::setMesh(GLMesh* mesh)
{
	_mesh = mesh;
}

void GLRenderer::setShaderProgram(GLShaderProgram* shaderProgram)
{
	_shaderProgram = shaderProgram;
}