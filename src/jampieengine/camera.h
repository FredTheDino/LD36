#pragma once

#include "transform.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Jam
{
	class Camera
	{
	public:
		Camera(glm::mat4 projection = glm::mat4(1.0f), Transform transform = {});
		
		//The transform of this camera
		Transform transform;

		//Fetches the projection matrix of this camera
		glm::mat4 getProjection() { return _projection; };

		//Fetches the view matrix of this camera
		glm::mat4 getView() { return glm::inverse(transform.getMatrix()); };

		//Returns the transform of this camera
		Transform getTransform() { return transform; };

		//Generates a perspective projection matrix
		static glm::mat4 perspective(float fieldOfView, float aspectRatio, float zNear, float zFar)
		{
			return glm::perspective(fieldOfView, aspectRatio, zNear, zFar);
		}

		//Generates an orthographic projection matrix
		static glm::mat4 orthographic(float left, float right, float bottom, float top)
		{
			return glm::ortho(left, right, bottom, top);
		}

	private:

		//The projection matrix of this camera
		glm::mat4 _projection;

	};
}