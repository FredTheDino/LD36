#pragma once

#include <iostream>
#include <thread>

#include "core.h"
#include "inputhandler.h"

namespace Jam
{
	//Forward declarations
	class Pie;
	struct Flavor;

	//GraphicsCore class for handling all graphics
	class LogicCore : Core
	{
	public:
		LogicCore(Pie& pie, Flavor& flavor);
		~LogicCore();

	private:

		//Thread used to process rendering
		std::thread* _thread;

		//Invoked by main class upon launch
		void _bake(Flavor& flavor);

		//Called by thread on start
		void _start();

		friend Pie;
	};
}