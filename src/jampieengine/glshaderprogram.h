#pragma once

#include <vector>
#include "glm/gtc/type_ptr.hpp"

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
		GLShaderProgram(ShaderProgram shaderProgram);
		~GLShaderProgram();

		void bind();

		GLuint getUniformLocation(std::string name) { return glGetUniformLocation(_id, name.c_str()); };

		void sendUniform1f(std::string uniform, float value) { glUniform1f(getUniformLocation(uniform), value); };
		void sendUniform1d(std::string uniform, double value) { glUniform1d(getUniformLocation(uniform), value); };
		void sendUniform1i(std::string uniform, int value) { glUniform1i(getUniformLocation(uniform), value); };

		void sendUniform2f(std::string uniform, float value1, float value2) { glUniform2f(getUniformLocation(uniform), value1, value2); };
		void sendUniform2d(std::string uniform, double value1, double value2) { glUniform2d(getUniformLocation(uniform), value1, value2); };
		void sendUniform2i(std::string uniform, int value1, int value2) { glUniform2i(getUniformLocation(uniform), value1, value2); };

		void sendUniform3f(std::string uniform, float value1, float value2, float value3) { glUniform3f(getUniformLocation(uniform), value1, value2, value3); };
		void sendUniform3d(std::string uniform, double value1, double value2, double value3) { glUniform3d(getUniformLocation(uniform), value1, value2, value3); };
		void sendUniform3i(std::string uniform, int value1, int value2, int value3) { glUniform3i(getUniformLocation(uniform), value1, value2, value3); };

		void sendUniform4f(std::string uniform, float value1, float value2, float value3, float value4) { glUniform4f(getUniformLocation(uniform), value1, value2, value3, value4); };
		void sendUniform4d(std::string uniform, double value1, double value2, double value3, double value4) { glUniform4d(getUniformLocation(uniform), value1, value2, value3, value4); };
		void sendUniform4i(std::string uniform, int value1, int value2, int value3, int value4) { glUniform4i(getUniformLocation(uniform), value1, value2, value3, value4); };

		void sendUniformMat4f(std::string uniform, glm::mat4 value) { glUniformMatrix4fv(getUniformLocation(uniform), 1, GL_FALSE, (GLfloat*) glm::value_ptr(value)); };
	private:

		std::vector<GLShader*> _shaders;

		GLuint _id;

	};
}