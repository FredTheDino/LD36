#pragma once

#include "glm/glm.hpp"

#include "audiohandler.h"

#include <chrono>

namespace Jam {
	class AudioListener {
	public:
		
		static glm::vec3 getPosition();
		static glm::vec3 getVelocity();
		static glm::vec3 getUp();
		static glm::vec3 getForward();
		static float getGain();

		static void setMasterVolume(float gain);
		static void setVelocity(float, float, float);
		static void setVelocity(glm::vec3 vel);
		static void setPosition(float, float, float);
		static void setPosition(glm::vec3 pos);
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
