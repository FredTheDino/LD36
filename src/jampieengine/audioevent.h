#pragma once

#include <string>

namespace Jam {

	//A namespace to hold specific types of data for audio events
	namespace AudioEventData {
		//The type of the event
		enum class Type {
			SET,
			PLAY,
			PAUSE,
			STOP
		};
		
		//If it is a set event, what should then be set
		enum class Target {
			GAIN,
			PITCH,
			POSITION,
			VELOCITY,
		};
	};

	typedef struct {
		//The type of the event
		AudioEventData::Type type;
		//The source that we want to manipulate
		unsigned int source;
		//The target for set operations
		AudioEventData::Target target;
		//Optional int data
		int iData[3];
		//Optional float data
		float fData[3];
		//A string for potential sounds files
		std::string path;
	}  AudioEvent;

}