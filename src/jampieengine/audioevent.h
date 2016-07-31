#pragma once

#include <string>

#include <AL/al.h>

namespace Jam {

	//A namespace to hold specific types of data for audio events
	namespace AudioEventData {
		//The type of the event
		enum class Type {
			SET,
			PLAY,
			PAUSE,
			STOP,
			REWIND,
			QUEUE, 
			CLEAR_QUEUE,
		};
		
		//If it is a set event, what should then be set
		enum class Target {
			//Allways
			LOOPING,
			BUFFER,
			GAIN,
			PITCH,
			//Spatial
			MAX_GAIN,
			MIN_GAIN,
			MAX_DISTANCE,
			ROLLOFF_FACTOR,
			POSITION,
			VELOCITY,
		};
	};

	typedef struct {

		//If it is a spatial sound or not
		bool isSpatial;
		//The type of the event
		AudioEventData::Type type;
		//The source that we want to manipulate
		ALuint source;
		//The target for set operations
		ALenum target;
		//Optional int data
		int iData[3];
		//Optional float data
		float fData[3];
		//A string for potential sounds files
		std::string nickname;
	}  AudioEvent;

}