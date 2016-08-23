#pragma once

#include <vector>

#include "audioevent.h"
#include "audiohandler.h"

namespace Jam {

	class AudioEventQueue {
	public:

		//Add an event to the queue
		static void pushDataToQueue(AudioEvent ae);
		//Copy over the queue and clear it of the data copied over
		static void copyQueue(std::vector<AudioEvent>& queue);

	private:

		//A list of the events that are yet to be proccessed
		static std::vector<AudioEvent> _events;
		//If the event list is being accessed at the moment
		static bool _accessingQueue;

		friend AudioHandler;

	};

}