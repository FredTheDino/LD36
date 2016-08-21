#pragma once

#include "audioevent.h"
#include "sound.h"

#include <string>
#include <vector>
#include <AL\al.h>
#include <AL\alc.h>

namespace Jam {

	class AudioLibrary;

	class AudioHandler {
		friend Sound;

	public:

		//Initalizes the engine
		static void init(AudioLibrary& library);

		//Destroys the engine
		static void destroy();

		//Update all the data in the engine
		static void update();

		//Preload a sound file
		static void preload(const std::string& nickname, const std::string& path);

		//Unload a sound file
		static void unload(const std::string& nickname);

		//If it is done loading
		static bool ready();

	private:

		//Generates a new AL source
		static ALuint _generateSource();
	
		//Generates a new AL source
		static void _destroySource(ALuint);

		//A helper function to for the set audio event
		static void _set(AudioEvent& e);

		//A helper function to set AL values linked to the listener
		static void _listener(AudioEvent& e);

		//A list of AL sources
		static std::vector<ALuint> _sources;
		//If something is accessing the _sources array
		static bool _accessingSource;

		//An OpenAL device
		static ALCdevice* _device;
		//An OpenAL context
		static ALCcontext* _context;
		//A refference to the audio library
		static AudioLibrary* _library;


	};
}