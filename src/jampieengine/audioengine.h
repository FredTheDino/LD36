#pragma once

#include "audioevent.h"

#include <string>
#include <vector>
#include <AL\al.h>
#include <AL\alc.h>

namespace Jam {

	class AudioEngine {
	public:
		AudioEngine();
		~AudioEngine();

		//Update all the data in the engine
		void update();

		//Preload a sound file
		bool preload(const std::string& path);

		//Unload a sound file
		bool unload(const std::string& path);

	private:

		//An OpenAL device
		ALCdevice* _device;
		//An OpenAL context
		ALCcontext* _context;

		//List of sound sources
		std::vector<ALuint> _soundSources;
		//List of sound sources with audio data
		std::vector<ALuint> _spatialSoundssources;



	};
}