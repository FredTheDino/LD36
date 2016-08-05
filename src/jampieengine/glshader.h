#pragma once

#include <string>

#include "GL/glew.h"

#include "glshaderprogram.h"
#include "debug.h"

namespace Jam
{
	//Forward declaration
	class GLShaderProgram;

	class GLShader
	{
	public:
		GLShader(std::string source, GLenum type);
		~GLShader();

	private:

		GLuint _id;

		void _attach(GLuint program);
		void _detach(GLuint program);

		friend GLShaderProgram;
	};
}