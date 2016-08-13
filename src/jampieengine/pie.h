#pragma once

#include <iostream>
#include <string>

#include <SDL2/SDL.h>

#include "graphicscore.h"
#include "logiccore.h"
#include "audiocore.h"
#include "debug.h"
#include "inputhandler.h"
#include "gamestatemanager.h"

namespace Jam
{
	//Forward declarations
	class GraphicsCore;
	class GameStateManager;

	//Struct used to retrieve startup information from user
	struct Flavor {
		std::string title = "My Pie";
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
		
		//GameStateManager
		GameStateManager* _gameStateManager;

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