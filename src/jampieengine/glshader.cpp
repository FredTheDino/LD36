#include "glshader.h"

using namespace Jam;

GLShader::GLShader(std::string source, GLenum type)
{
	_id = glCreateShader(type);

	const char* data = source.c_str();
	glShaderSource(_id, 1, &data, NULL);

	glCompileShader(_id);

	GLint result = GL_FALSE;
	int logLength;

	glGetShaderiv(_id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &logLength);
	if (result == GL_FALSE) {
		std::vector<char> error(logLength);
		glGetShaderInfoLog(_id, logLength, NULL, error.data());
		Debug::err("Failed to compile shader: " + std::string(error.data()), _id);
	}
}

void GLShader::_attach(GLuint program)
{
	glAttachShader(program, _id);
}

void GLShader::_detach(GLuint program)
{
	glDetachShader(program, _id);
}

GLShader::~GLShader()
{
	glDeleteShader(_id);
}