#pragma once

#include <string>

namespace Jam
{
	struct ShaderProgram {
		std::string vertexShader;
		std::string tessControlShader;
		std::string tessEvaluationShader;
		std::string geometryShader;
		std::string fragmentShader;
		std::string computeShader;
	};
}