#pragma once

#include <iostream>
#include <string>

#include <SDL2/SDL.h>

#include "graphicscore.h"
#include "audiocore.h"
#include "debug.h"
#include "inputhandler.h"
#include "gamestatemanager.h"
#include "camera.h"

namespace Jam
{
	//Forward declarations
	class GraphicsCore;
	class GameStateManager;

	//Struct used to retrieve startup information from user
	struct Flavor {
		std::string title = "My Pie";
		std::string inputmap = "input.map";
		std::string enterState = "main";
		unsigned int w_width = 800;
		unsigned int w_height = 600;
		bool w_border = true;
		bool w_resizable = false;
		GraphicsCoreType graphicsCoreType = GRAPHICS_TYPE_OPENGL;
		Camera* camera = nullptr;
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

		GraphicsCore* getGraphicsCore() { return _graphicsCore; };
		AudioCore* getAudioCore() { return _audioCore; };
		GameStateManager* getGameStateManager() { return _gameStateManager; };

	private:

		//True if the engine is running
		bool _cooking = false;

		//User information saved
		Flavor& _flavor;
		
		//GameStateManager
		GameStateManager* _gameStateManager = nullptr;

		//Core handles
		GraphicsCore* _graphicsCore = nullptr;
		AudioCore* _audioCore = nullptr;

		//Initialization functions
		void _initSDL();
		void _initCores();

		//Friends!
		friend GraphicsCore;
		friend AudioCore;
	};
}