#pragma once

#include <iostream>
#include <thread>

#include "graphicscoretype.h"
#include "window.h"
#include "pie.h"

namespace Jam
{
	//Forward declarations
	class Window;
	class Pie;
	struct Flavor;

	//GraphicsCore class for handling all graphics
	class GraphicsCore
	{
	public:
		GraphicsCore(Pie& pie, Flavor& flavor);
		~GraphicsCore();

	private:

		//Main class reference
		Pie& _pie;

		//Thread used to process rendering
		std::thread* _thread;

		//The window class pointer
		Window* _window;

		//Invoked by main class upon launch
		void _bake(Flavor& flavor);

		//Called by thread on start
		void _start();

		friend Pie;
	};
}