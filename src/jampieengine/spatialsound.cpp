#include "spatialsound.h"

#include "audioeventqueue.h"

#include <AL/al.h>

namespace Jam {

	SpatialSound::SpatialSound() : Sound() {
		_setPosition(_position);
		_setVelocity(_velocity);
	}

	SpatialSound::~SpatialSound() {}

	void SpatialSound::_setPosition(glm::vec3 position) {
		AudioEvent ae;
		ae.source = _source;
		ae.type = AudioEventData::Type::SET;
		ae.target = AL_POSITION;
		ae.fData[0] = position[0];
		ae.fData[1] = position[1];
		ae.fData[2] = position[2];
		AudioEventQueue::pushDataToQueue(ae);
		_position = position;
	}

	void SpatialSound::_setVelocity(glm::vec3 velocity) {
		AudioEvent ae;
		ae.source = _source;
		ae.type = AudioEventData::Type::SET;
		ae.target = AL_VELOCITY;
		ae.fData[0] = velocity[0];
		ae.fData[1] = velocity[1];
		ae.fData[2] = velocity[2];
		AudioEventQueue::pushDataToQueue(ae);
		_velocity = velocity;
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

