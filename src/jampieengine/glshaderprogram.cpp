#include "glshaderprogram.h"

using namespace Jam;

GLShaderProgram::GLShaderProgram(ShaderProgram shaderProgram)
{
	//Generate vertex shader if available
	if (shaderProgram.vertexShader.length()) {
		_shaders.push_back(new GLShader(shaderProgram.vertexShader, GL_VERTEX_SHADER));
	}

	//Generate tesselation control shader if available
	if (shaderProgram.tessControlShader.length()) {
		_shaders.push_back(new GLShader(shaderProgram.tessControlShader, GL_TESS_CONTROL_SHADER));
	}

	//Generate tesselation evaluation shader if available
	if (shaderProgram.tessEvaluationShader.length()) {
		_shaders.push_back(new GLShader(shaderProgram.tessEvaluationShader, GL_TESS_EVALUATION_SHADER));
	}

	//Generate geometry shader if available
	if (shaderProgram.geometryShader.length()) {
		_shaders.push_back(new GLShader(shaderProgram.geometryShader, GL_GEOMETRY_SHADER));
	}

	//Generate fragment shader if available
	if (shaderProgram.fragmentShader.length()) {
		_shaders.push_back(new GLShader(shaderProgram.fragmentShader, GL_FRAGMENT_SHADER));
	}

	//Generate compute shader if available
	if (shaderProgram.computeShader.length()) {
		_shaders.push_back(new GLShader(shaderProgram.computeShader, GL_COMPUTE_SHADER));
	}

	//Create program
	_id = glCreateProgram();

	//Attach shaders
	for (GLShader* shader : _shaders) {
		shader->_attach(_id);
	}

	//Link program
	glLinkProgram(_id);

	GLint result = GL_FALSE;
	int logLength;

	glGetProgramiv(_id, GL_LINK_STATUS, &result);
	glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &logLength);
	if (result == GL_FALSE) {
		std::vector<char> error(logLength);
		glGetProgramInfoLog(_id, logLength, NULL, error.data());
		Debug::err(error.data(), _id);
	}

	//Validate program
	glValidateProgram(_id);

	glGetProgramiv(_id, GL_VALIDATE_STATUS, &result);
	glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &logLength);
	if (result == GL_FALSE) {
		std::vector<char> error(logLength);
		glGetProgramInfoLog(_id, logLength, NULL, error.data());
		Debug::err(error.data(), _id);
	}

	//Detach shaders
	for (GLShader* shader : _shaders) {
		shader->_detach(_id);
	}
}

void GLShaderProgram::bind()
{
	glUseProgram(_id);
}

GLShaderProgram::~GLShaderProgram()
{
	//Delete shaders
	for (GLShader* shader : _shaders) {
		delete shader;
	}

	//Clear shader vector
	_shaders.clear();
}