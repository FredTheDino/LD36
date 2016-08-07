#pragma once

#include <vector>

#include "GL/glew.h"

#include "glshader.h"
#include "shaderprogram.h"

namespace Jam
{
	//Forward declaration
	class GLShader;

	class GLShaderProgram
	{
	public:
		GLShaderProgram(ShaderProgram& shaderProgram);
		~GLShaderProgram();

		void bind();

	private:

		std::vector<GLShader*> _shaders;

		GLuint _id;

	};
}