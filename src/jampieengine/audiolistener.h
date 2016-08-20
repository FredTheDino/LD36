#pragma once

#include "glm/glm.hpp"

#include "audiohandler.h"

#include <chrono>

namespace Jam {
	class AudioListener {
	public:

		//Getters
		//Gets the position
		static glm::vec3 getPosition();
		//Gets the velocity
		static glm::vec3 getVelocity();
		//Gets the rotational up vector
		static glm::vec3 getUp();
		//Gets the rotational forward vector
		static glm::vec3 getForward();
		//Returns the gain
		static float getGain();

		//Setters
		//Sets the master gain/volume
		static void setMasterVolume(float gain);
		//A wrapper for setting the velocity nice and easy
		static void setVelocity(float, float, float);
		//Settings the velocity
		static void setVelocity(glm::vec3 vel);
		//Set the position in a  nice and simple way
		static void setPosition(float, float, float);
		//Set the position using glm vectors
		static void setPosition(glm::vec3 pos);
		//Set the two vectors as only a floats
		static void setOrientation(float, float, float, float, float, float);
		static void setOrientation(glm::vec3 forward, glm::vec3 up = _up);

	private:

		static float _gain;

		static glm::vec3 _position;
		static glm::vec3 _velocity;
		static glm::vec3 _up;
		static glm::vec3 _forward;
	};
}
