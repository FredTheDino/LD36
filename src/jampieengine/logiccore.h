#pragma once

#include <iostream>
#include <thread>

#include "inputhandler.h"

namespace Jam
{
	//Forward declarations
	class Pie;
	struct Flavor;

	//GraphicsCore class for handling all graphics
	class LogicCore
	{
	public:
		LogicCore(Pie& pie, Flavor& flavor);
		~LogicCore();

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