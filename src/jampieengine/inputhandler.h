#pragma once

/////////////////////////////////////////////////////
// NOTE FOR THE FUTURE!                            //
// There is still alot left to do with this class. //
// Controller support and io are the 2 main ones.  //
// Have a nice one future person! :D               //
/////////////////////////////////////////////////////

//Dude, there's a mouse too...

#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <thread>

#include <SDL2\SDL.h>

namespace Jam {

	//The key states for digital input (multiple can be active
	enum KeyState {
		//If not helt down
		UP = 0x0,
		//If held down
		DOWN = 0x1,
		//If released this frame
		RELEASED = 0x2,
		//If pressed this frame
		PRESSED = 0x4
	};

	//A simple input data structure with a simple function for easy equallity checks
	struct InputData {

		//Ease of use constructor
		InputData(const std::string& name, bool isScancode, int dev, int mods, int code): 
			name(name), isScancode(isScancode), dev(dev), mods(mods), code(code) {}

		//Ease of use equallity check for linear search
		bool operator== (InputData& data) {
			return 
				data.isScancode == isScancode &&
				data.dev == dev &&
				data.mods == mods &&
				data.code == code;
		}
		
		//Name of the input
		std::string name;
		//If code is a scancode or a keycode
		bool isScancode;
		//Which device this is registerd to, -1 is keyboard the rest are controllers
		int dev;
		//Any modifiers (alt, shift, etc...) for this input event, requiers a keyboard
		int mods;
		//The key/button/axis-code
		int code;
		//The state of the key/button
		short status = KeyState::UP;
		//The value of the axis normalized between -1 and 1
		double axis = 0.0;
	};

	class InputHandler {
	public:
		//The initalization function, should be called from Pie::Pie()
		static void init();
		//The deinitalization funciton, does some cleanup and should be called as Pie::Bake() ends
		static void destroy();
		//Check if the loading is compleated and this component is ready to proceede in execution
		static bool ready();
		//The update call that updates all the inputData
		static void update();

		//Add an event to the event queue, to make this compatible with different threads
		//////////////////////////////////////////////////////////////////
		// NOTE: it is deliberately not passed in as a pointer to make	//
		// sure a new instance of the struct is saved in the object		//
		//////////////////////////////////////////////////////////////////
		static void pushEventToQueue(SDL_Event e);

		//Register an input event for future use, returns true if success
		//////////////////////////////////////////////////////////////////
		// NOTE: it is deliberately not passed in as a pointer to make	//
		// sure a new instance of the struct is saved in the object		//
		//////////////////////////////////////////////////////////////////
		static bool registerInput(InputData data);
		//Check if the state of digital input matches with the given
		static bool checkInputState(const std::string& name, KeyState keyState);

		//Functions for passing events to the inputhandler
		static void keyEvent(bool wasPressed, InputData& data);
		static void buttonEvent(bool wasPressed, InputData& data);
		static void axisEvent(InputData& data);
		static void controllerConnectionEvent(bool connect, int which);
	private:
		
		//Simple method to find a _inputList entry by name
		static InputData* _find(const std::string& name);
		//Simple method to find a _inputList entry by data
		static InputData* _find(InputData& data);

		//A function for loading input data from disk
		static void _load();
		//A funciton for saving input datat to disk
		static void _save();
		
		//A thread to run _load() and _save() to prevent clogging of main thread
		static std::thread* _ioThread;
		//Weather or not the ioThread has been initalized
		static bool _ioThreadExists;
		//The list of all currently registerd inputs, only for use in this class
		static std::unordered_map<std::string, InputData> _inputList;
		
		//The buffer for input events
		static std::vector<SDL_Event> _eventQueue;

		//The list of controllers that are currently active
		static std::vector<SDL_GameController*> _controllers;
		//Holds reffernces to controllers and replaced their device to allow for reusability
		static std::vector<short> _controllerRemapper;
	};
}