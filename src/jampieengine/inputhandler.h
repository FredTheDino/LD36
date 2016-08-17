#pragma once

/////////////////////////////////////////////////////
// NOTE FOR THE FUTURE!                            //
// IO still needs to be done. Just FYI             //
// Have a nice one future person! :D               //
/////////////////////////////////////////////////////

#include "inputeventqueue.h"
#include "inputdatatypes.h"
#include "pie.h"

#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <thread>

#include <SDL2/SDL.h>
#include "glm/glm.hpp"

namespace Jam {

	class InputHandler {
	public:

		//The initalization function, should be called from Pie::Pie()
		static void init(Flavor &flavor);
		//The deinitalization funciton, does some cleanup and should be called as Pie::Bake() ends
		static void destroy();
		//Check if the loading is compleated and this component is ready to proceede in execution
		static bool ready();
		//The update call that updates all the inputData
		static void update();

		//Register an input event for future use, returns true if success
		//////////////////////////////////////////////////////////////////
		// NOTE: it is deliberately not passed in as a pointer to make	//
		// sure a new instance of the struct is saved in the object		//
		//////////////////////////////////////////////////////////////////
		static bool registerInput(const std::string& name, InputBinding data);
		//Check if the state of digital input matches with the given
		static bool checkInputState(const std::string& name, KeyState keyState);
		//Returns the value of the axis of that input data
		static double getAxisData(const std::string& name);
		//Fetches the input data object
		static InputData getInputData(const std::string& name);
		//Returns the delta movement of the mouse
		static glm::vec2 getMouseDelta();
		//Returns the position of the mouse
		static glm::vec2 getMousePos();
		
		//Helper functions
		//Check if key is down
		static bool keyDown(const std::string& name);
		//Check if key is up
		static bool keyUp(const std::string& name);
		//Check if key is pressed
		static bool keyPressed(const std::string& name);
		//Check if key is released
		static bool keyReleased(const std::string& name);


		//Functions for passing events to the inputhandler
		static void digitalEvent(bool wasPressed, InputBinding& binding);
		static void axisEvent(double axis, InputBinding& binding);
		static void controllerConnectionEvent(bool connect, int which);

	private:

		//Simple method to find a _inputList entry by name
		static InputData* _find(const std::string& name);
		//Simple method to find a _inputList entry by data
		static InputData* _find(InputBinding& binding);

		//A function for loading input data from disk
		static void _load();
		//A funciton for saving input datat to disk
		static void _save();
		
		static Flavor* _flavor;

		//A thread to run _load() and _save() to prevent clogging of main thread
		static std::thread* _ioThread;
		//Weather or not the ioThread has been initalized
		static bool _ioThreadExists;
		//The mapper that maps an input to a name
		static std::unordered_map<InputBinding, std::string> _inputMapper;
		//The list of all currently registerd inputs, only for use in this class
		static std::unordered_map<std::string, InputData> _inputDataList;
		
		//An object to hold the mouse position
		static MousePos _mouse;
		//Hides the mouse
		static bool _hideMouse;
		//Centers the mouse
		static bool _centerMouse;
		//Something is reading/writing to _mouse
		static bool _accessingMouse;

		//The list of controllers that are currently active
		static std::vector<SDL_GameController*> _controllers;
		//Holds reffernces to controllers and replaced their device to allow for reusability
		static std::vector<short> _controllerRemapper;
		//If you're accessing the controllers form another thread
		static bool _accessingControllers;
	};
}