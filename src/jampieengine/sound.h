#pragma once

#include <string>
#include <AL/al.h>

#include "audioevent.h"

namespace Jam {

	class Sound {
	public:
		
		//Constructor
		Sound();

		//Destructor
		~Sound();

		//Play a sound
		void play();
		//Play a specified sound
		void play(const std::string& nickname);

		//Pause the player
		void pause();

		//Stop the player
		void stop();

		//Rewind to the begining of the buffer
		void rewind();

		//Queue another buffer that will play after this
		void queue(const std::string& nickname);

		//Clear the queue
		void clearQueue();

		//Set the current buffer
		void setBuffer(const std::string& nickname);

		//Set the gain/volume
		void setGain(float gain);
		
		//Set the pitch 
		void setPitch(float pitch);

		//Set if the sound should loop or not
		void setLooping(bool looping);

	protected:

		//A helper function to simplify sending of simple events
		void _sendEventOfType(AudioEventData::Type type);

		//This sounds audio source
		ALuint _source;

	};
}