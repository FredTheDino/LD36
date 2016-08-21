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

		void setMaxGain(float maxGain);
		void setMinGain(float minGain);
		void setMaxDistance(float maxDistance);
		void setRolloffFactor(RolloffFactor rolloff);

	protected:
		void _setPosition(glm::vec3 position);

		void _setVelocity(glm::vec3 velocity);

		glm::vec3 _position;
		glm::vec3 _velocity;


	};
}