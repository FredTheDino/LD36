#pragma once

#include <thread>

#include "jamtime.h"

namespace Jam {
	//Forward declarations
	class Pie;
	struct Flavor;
	class JamTime;

	//GraphicsCore class for handling all graphics
	class Core {
	public:
		Core(Pie& pie);
		~Core();

		void join();

	protected:

		//Thread used to process rendering
		std::thread* _thread;

		//Main class reference
		Pie& _pie;

		//Invoked by main class upon launch
		virtual void _bake(Flavor& flavor) =0;

		//Called by thread on start
		virtual void _start() =0;

		friend Pie;
	};
}