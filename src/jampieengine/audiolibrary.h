#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <thread>

#include <AL/al.h>
#include <AL/alc.h>

namespace Jam {

	class AudioLibrary {
	public:
		
		AudioLibrary();
		~AudioLibrary();

		//Preloads an audio file from RAM
		void preload(std::string nickname, std::string path);
		
		//Unloads an audio file from RAM
		void unload(std::string nickname);

		//Returns a buffer that is preloaded, other wise 0
		ALuint operator[] (const std::string& nickname);
		//If the library currently isn't loading anything
		bool ready();

		//Update the library and chekc if something new can be loaded
		void update();

	private:
		
		//A function to load and processs input
		void _load(std::string, std::string);

		//A thread that manages reading and writing
		std::thread* _ioThread = nullptr;
		//If the thread is ready to play audio
		bool _ready = true;

		//A list of sound files to be preloaded
		std::unordered_map<std::string, std::string> _preloadingQueue;
		//If something is accessing the preloaderqueue
		bool _accessingPreloadingQueue = false;

		//A lost of sound files to be unloaded from memory
		std::vector<std::string> _unloadingQueue;
		//If something is accessing the unloaderqueue
		bool _accessingUnloadingQueue = false;

		//The files loaded to ram
		//nickname, soundBuffer
		std::unordered_map<std::string, ALuint> _library;
		//If something is accessing the library map
		bool _accessingLibrary = false;
	};
}