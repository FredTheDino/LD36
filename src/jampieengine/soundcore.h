#pragma once

#include <iostream>
#include <thread>

namespace Jam {
	//Forward declarations
	class Pie;
	struct Flavor;

	//GraphicsCore class for handling all graphics
	class SoundCore {
	public:
		SoundCore(Pie& pie, Flavor& flavor);
		~SoundCore();

	private:

		//Main class reference
		Pie& _pie;

		//Thread used to process rendering
		std::thread* _thread;

		//Invoked by main class upon launch
		void _bake(Flavor& flavor);

		//Called by thread on start
		void _start();

		friend Pie;
	};
}