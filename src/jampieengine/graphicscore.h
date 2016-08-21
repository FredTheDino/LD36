#pragma once

#include <iostream>
#include <thread>

#include "core.h"
#include "graphicscoretype.h"
#include "window.h"
#include "renderengine.h" 
#include "pie.h"

namespace Jam
{
	//Forward declarations
	class Window;
	class Pie;
	class RenderEngine;
	struct Flavor;

	//GraphicsCore class for handling all graphics
	class GraphicsCore : Core
	{
	public:
		GraphicsCore(Pie& pie, Flavor& flavor);
		~GraphicsCore();

		RenderEngine* getRenderEngine() { return _renderEngine; };

	private:

		//Indicates to Pie if this core is properly set up
		bool _ready = false;

		//The window class pointer
		Window* _window;

		//The Render Engine
		RenderEngine* _renderEngine;

		//Invoked by main class upon launch
		void _bake(Flavor& flavor);

		//Called by thread on start
		void _start();

		friend Pie;
	};
}