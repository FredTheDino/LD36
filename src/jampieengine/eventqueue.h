#pragma once

#include <vector>

#include <SDL2/SDL.h>

namespace Jam {

	class EventQueue {
	public:

		//Add an event to the event queue, to make this compatible with different threads
		//////////////////////////////////////////////////////////////////
		// NOTE: it is deliberately not passed in as a pointer to make	//
		// sure a new instance of the struct is saved in the object		//
		//////////////////////////////////////////////////////////////////
		static void pushEventToQueue(SDL_Event e);

		//Copies the eventqueue safe and secure
		static void copyEventQueue(std::vector<SDL_Event>* target);

	private:

		//The buffer for input events
		static std::vector<SDL_Event> _queue;
		//A bool to make sure the queueu is not writen to and read from at the same time
		static bool _queueIsUsed;

	};
}