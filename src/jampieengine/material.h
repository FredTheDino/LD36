#pragma once

#include <string>

#include "glm/glm.hpp"

namespace Jam
{
	struct Material {
		glm::vec4 baseColor = glm::vec4(1.0f);
		std::string texture = "default";
		bool spriteSheet = false;
		unsigned int ssOffsetX;
		unsigned int ssOffsetY;
	};
}