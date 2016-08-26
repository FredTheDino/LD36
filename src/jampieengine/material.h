#pragma once

#include <string>

#include "glm/glm.hpp"

namespace Jam
{
	struct Material {

		std::string texture = "default";
		glm::vec4 baseColor = glm::vec4(1.0f);
	};
}