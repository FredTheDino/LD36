#pragma once

#include "sound.h"
#include "glm/glm.hpp"

namespace Jam {

	enum class RolloffFactor {
		LINEAR,
		INVERSE,
		EXPONENTIAL
	};

	class SpatialSound : public Sound {

	public:
		SpatialSound();
		~SpatialSound();

		void setPosition(float x, float y, float z);
		void setPosition(glm::vec3 position);

		void setVelocity(float x, float y, float z);
		void setVelocity(glm::vec3 velocity);

		void setMaxGain(float maxGain);
		void setMinGain(float minGain);
		void setMaxDistance(float maxDistance);
		void setRolloffFactor(RolloffFactor rolloff);
	};
}