#pragma once

#include <string>
#include <AL/al.h>
#include <vector>

#include "audioevent.h"
#include "soundfade.h"

namespace Jam {

	class Sound {
	public:
		
		//Constructor
		Sound();

		//Destructor
		~Sound();

		//Helper function to fade the gain
		void fadeGain(float target, float time);

		//Helper function to fade the pitch
		void fadePitch(float target, float time);

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

		//Update all the fadeing stuff
		void updateFade(double delta);

		//Returns if it is playing
		bool isPlaying();

		//Returns if it is paused
		bool isPaused();

		//Returns if it is looping
		bool isLooping();

		//Returns if it is stopped
		bool isStopped();

	protected:

		//A copy to the gian
		float _gain = 1.0;
		//A copy to the pitch
		float _pitch = 1.0;
		//A copy to the looping
		bool _looping = false;
		//A copy to playing
		bool _playing = false;
		//A copy of isStopped
		bool _stopped = true;

		//A helper function to simplify sending of simple events
		void _sendEventOfType(AudioEventData::Type type);

		//This sounds audio source
		ALuint _source;

		//Somethign to hold all the fade events
		std::vector<FadeData> _fadeValues;
	};
}