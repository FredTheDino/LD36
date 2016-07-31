#pragma once

#include <iostream>
#include <thread>

#include <AL/al.h>
#include <AL/alc.h>

#include "audiolibrary.h"

namespace Jam {
	//Forward declarations
	class Pie;
	struct Flavor;

	//GraphicsCore class for handling all graphics
	class AudioCore {
	public:
		AudioCore(Pie& pie, Flavor& flavor);
		~AudioCore();

	private:

		//Main class reference
		Pie& _pie;

		//Thread used to process rendering
		std::thread* _thread;

		//Invoked by main class upon launch
		void _bake(Flavor& flavor);

		//Called by thread on start
		void _start();

		//The input device to use
		ALCdevice* _device;
		//The AL context
		ALCcontext* _context;

		AudioLibrary _library;

		ALuint _source;
		ALuint _buffer;

		friend Pie;
	};
}