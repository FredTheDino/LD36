#pragma once

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

namespace Jam
{
	struct Transform {
		glm::vec3 position = glm::vec3();
		glm::vec3 scale = glm::vec3(1, 1, 1);
		glm::vec3 rotation = glm::vec3();

		glm::mat4 getMatrix()
		{
			glm::mat4 mat = glm::translate(position);
			mat = glm::rotate(mat, rotation.x, glm::vec3(1, 0, 0));
			mat = glm::rotate(mat, rotation.y, glm::vec3(0, 1, 0));
			mat = glm::rotate(mat, rotation.z, glm::vec3(0, 0, 1));
			mat = glm::scale(mat, scale);
			
			return mat;
		}

		void translate(glm::vec2 offset)
		{
			position.x += offset.x;
			position.y += offset.y;
		}

		void translate(glm::vec3 offset)
		{
			position.x += offset.x;
			position.y += offset.y;
			position.z += offset.z;
		}

		void translate(float x, float y, float z = 0)
		{
			translate(glm::vec3(x, y, z));
		}

		void translateX(float x)
		{
			translate(glm::vec2(x, 0));
		}

		void translateY(float y)
		{
			translate(glm::vec2(0, y));
		}

		void translateZ(float z)
		{
			translate(glm::vec3(0, 0, z));
		}

		void setPosition(glm::vec2 position)
		{
			this->position.x = position.x;
			this->position.y = position.y;
		}

		void setPosition(glm::vec3 position)
		{
			this->position = position;
		}

		void setPosition(float x, float y, float z)
		{
			setPosition(glm::vec3(x, y, z));
		}

		void setPosition(float x, float y)
		{
			setPosition(glm::vec2(x, y));
		}

		void setX(float x)
		{
			position.x = x;
		}

		void setY(float y)
		{
			position.y = y;
		}

		void setZ(float z)
		{
			position.z = z;
		}

		void scaleT(glm::vec2 scale)
		{
			this->scale.x *= scale.x;
			this->scale.y *= scale.y;
		}

		void scaleT(glm::vec3 scale)
		{
			this->scale.x *= scale.x;
			this->scale.y *= scale.y;
			this->scale.z *= scale.z;
		}

		void scaleT(float x, float y, float z = 1)
		{
			scale.x *= x;
			scale.y *= y;
			scale.z *= z;
		}

		void scaleX(float x)
		{
			scale.x *= x;
		}

		void scaleY(float y)
		{
			scale.y *= y;
		}

		void scaleZ(float z)
		{
			scale.z *= z;
		}

		void scaleT(float scalar)
		{
			scale *= scalar;
		}

		void addScale(glm::vec2 scale)
		{
			this->scale.x += scale.x;
			this->scale.y += scale.y;
		}

		void addScale(glm::vec3 scale)
		{
			this->scale.x += scale.x;
			this->scale.y += scale.y;
			this->scale.z += scale.z;
		}

		void addScale(float x, float y, float z = 0)
		{
			addScale(glm::vec3(x, y, z));
		}

		void addScaleX(float x)
		{
			scale.x += x;
		}

		void addScaleY(float y)
		{
			scale.y += y;
		}

		void addScaleZ(float z)
		{
			scale.z += z;
		}

		void addScale(float scale)
		{
			addScale(scale, scale, scale);
		}

		void setScale(glm::vec2 scale)
		{
			this->scale.x = scale.x;
			this->scale.y = scale.y;
		}

		void setScale(glm::vec3 scale)
		{
			this->scale = scale;
		}

		void setScale(float x, float y)
		{
			setScale(glm::vec2(x, y));
		}

		void setScale(float x, float y, float z)
		{
			setScale(glm::vec3(x, y, z));
		}

		void setScaleX(float x)
		{
			scale.x = x;
		}

		void setScaleY(float y)
		{
			scale.y = y;
		}

		void setScaleZ(float z)
		{
			scale.z = z;
		}

		void setScale(float scale)
		{
			setScale(scale, scale, scale);
		}

		void rotate(glm::vec3 rotation)
		{
			this->rotation.x += rotation.x;
			this->rotation.y += rotation.y;
			this->rotation.z += rotation.z;
		}

		void rotate(float x, float y, float z)
		{
			rotate(glm::vec3(x, y, z));
		}

		void rotateX(float x)
		{
			rotation.x += x;
		}

		void rotateY(float y)
		{
			rotation.y += y;
		}

		void rotateZ(float z)
		{
			rotation.z += z;
		}

		void setRotation(glm::vec3 scale)
		{
			this->rotation = rotation;
		}

		void setRotation(float x, float y, float z)
		{
			setRotation(glm::vec3(x, y, z));
		}

		void setRX(float x)
		{
			rotation.x = x;
		}

		void setRY(float y)
		{
			rotation.y = y;
		}

		void setRZ(float z)
		{
			rotation.z = z;
		}

	};
}