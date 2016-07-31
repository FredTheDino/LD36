#include "spatialsound.h"

#include "audioeventqueue.h"

#include <AL/al.h>

namespace Jam {

	SpatialSound::SpatialSound() : Sound() {

	}

	SpatialSound::~SpatialSound() {}

	void SpatialSound::setPosition(float x, float y, float z) {
		setPosition(glm::vec3(x, y, z));
	}

	void SpatialSound::setPosition(glm::vec3 position) {
		AudioEvent ae;
		ae.source = _source;
		ae.type = AudioEventData::Type::SET;
		ae.target = AL_POSITION;
		ae.fData[0] = position[0];
		ae.fData[1] = position[1];
		ae.fData[2] = position[2];
		AudioEventQueue::pushDataToQueue(ae);
	}

	void SpatialSound::setVelocity(float x, float y, float z) {
		setVelocity(glm::vec3(x, y, z));
	}

	void SpatialSound::setVelocity(glm::vec3 velocity) {
		AudioEvent ae;
		ae.source = _source;
		ae.type = AudioEventData::Type::SET;
		ae.target = AL_VELOCITY;
		ae.fData[0] = velocity[0];
		ae.fData[1] = velocity[1];
		ae.fData[2] = velocity[2];
		AudioEventQueue::pushDataToQueue(ae);
	}

	void SpatialSound::setMaxGain(float maxGain) {
		AudioEvent ae;
		ae.source = _source;
		ae.type = AudioEventData::Type::SET;
		ae.target = AL_MAX_GAIN;
		ae.fData[0] = maxGain;
		AudioEventQueue::pushDataToQueue(ae);
	}

	void SpatialSound::setMinGain(float minGain) {
		AudioEvent ae;
		ae.source = _source;
		ae.type = AudioEventData::Type::SET;
		ae.target = AL_MIN_GAIN;
		ae.fData[0] = minGain;
		AudioEventQueue::pushDataToQueue(ae);
	}

	void SpatialSound::setMaxDistance(float maxDistance) {
		AudioEvent ae;
		ae.source = _source;
		ae.type = AudioEventData::Type::SET;
		ae.target = AL_MAX_DISTANCE;
		ae.fData[0] = maxDistance;
		AudioEventQueue::pushDataToQueue(ae);
	}

	void SpatialSound::setRolloffFactor(RolloffFactor rolloff) {
		AudioEvent ae;
		ae.source = _source;
		ae.type = AudioEventData::Type::SET;
		ae.target = AL_ROLLOFF_FACTOR;

		switch (rolloff) {
			case Jam::RolloffFactor::LINEAR:
				ae.iData[0] = AL_LINEAR_DISTANCE;
				break;
			case Jam::RolloffFactor::INVERSE:
				ae.iData[0] = AL_INVERSE_DISTANCE;
				break;
			case Jam::RolloffFactor::EXPONENTIAL:
				ae.iData[0] = AL_EXPONENT_DISTANCE;
				break;
			default:
				break;
		}

		AudioEventQueue::pushDataToQueue(ae);
	}
}

