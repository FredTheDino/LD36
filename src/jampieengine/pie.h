#pragma once

#include <iostream>
#include <string>

#include <SDL2/SDL.h>

#include "graphicscore.h"
#include "logiccore.h"
#include "audiocore.h"
#include "debug.h"
#include "inputhandler.h"

namespace Jam
{
	//Forward declaration of GraphicsCore
	class GraphicsCore;

	//Struct used to retrieve startup information from user
	struct Flavor {
		std::string title = "My Pie";
		std::string inputmap = "input.map";
		unsigned int w_width = 800;
		unsigned int w_height = 600;
		bool w_border = true;
		bool w_resizable = false;
		GraphicsCoreType graphicsCoreType = GRAPHICS_TYPE_OPENGL;
	};

	//Main class definition
	class Pie {
	public:
		Pie(Flavor& flavor);
		~Pie();

		//Starts engine
		void bake();

		//Returns true if the engine is running
		bool isCooking() { return _cooking; };

		//Called to stop engine
		void eat() { _cooking = false; };

	private:

		//True if the engine is running
		bool _cooking = false;

		//User information saved
		Flavor& _flavor;

		//Core handles
		GraphicsCore* _graphicsCore;
		LogicCore* _logicCore;
		AudioCore* _soundCore;

		//Initialization functions
		void _initSDL();
		void _initCores();

		//Friends!
		friend GraphicsCore;
		friend LogicCore;
		friend AudioCore;
	};
}