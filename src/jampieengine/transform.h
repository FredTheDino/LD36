#pragma once

#include "glm/glm.hpp"

namespace Jam
{
	struct Transform {
		glm::vec3 position;
		glm::vec3 scale;
		glm::vec3 rotation;

		glm::mat4 getMatrix()
		{
			glm::mat4 pos(glm::vec4(1, 0, 0, position.x), glm::vec4(0, 1, 0, position.y), glm::vec4(0, 0, 1, position.z), glm::vec4(0, 0, 0, 1));
			glm::mat4 rx(glm::vec4(1, 0, 0, 0), glm::vec4(0, cos(rotation.x), -sin(rotation.x), 0), glm::vec4(0, sin(rotation.x), cos(rotation.x), 0), glm::vec4(0, 0, 0, 1));
			glm::mat4 ry(glm::vec4(cos(rotation.y), 0, sin(rotation.y), 0), glm::vec4(0, 1, 0, 0), glm::vec4(-sin(rotation.y), 0, cos(rotation.y), 0), glm::vec4(0, 0, 0, 1));
			glm::mat4 rz(glm::vec4(cos(rotation.z), -sin(rotation.z), 0, 0), glm::vec4(sin(rotation.z), cos(rotation.z), 0, 0), glm::vec4(0, 0, 1, 0), glm::vec4(0, 0, 0, 1));
			glm::mat4 scale(glm::vec4(scale.x, 0, 0, 0), glm::vec4(0, scale.y, 0, 0), glm::vec4(0, 0, scale.z, 0), glm::vec4(0, 0, 0, 1));

			return pos * rx * ry * rz * scale;
		}
	};
}