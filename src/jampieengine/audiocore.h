#pragma once

#include <iostream>
#include <thread>

#include <AL/al.h>
#include <AL/alc.h>

#include "core.h"
#include "audiolibrary.h"
#include "audiohandler.h"

namespace Jam {
	//Forward declarations
	class Pie;
	struct Flavor;

	//GraphicsCore class for handling all graphics
	class AudioCore : Core {
	public:
		AudioCore(Pie& pie, Flavor& flavor);
		~AudioCore();

	protected:

		//Thread used to process rendering
		std::thread* _thread;

		//Invoked by main class upon launch
		void _bake(Flavor& flavor);

		//Called by thread on start
		void _start();

		//A library to hold all the buffers
		AudioLibrary _library;
		//The actual computation engine coupled with the audio
		AudioHandler _handler;

		friend Pie;
	};
}