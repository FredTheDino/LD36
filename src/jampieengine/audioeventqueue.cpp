#include "audioeventqueue.h"

namespace Jam {

	std::vector<AudioEvent> AudioEventQueue:: _events;
	bool AudioEventQueue::_accessingQueue;

	void AudioEventQueue::pushDataToQueue(AudioEvent ae) {
		while (_accessingQueue) {}
		_accessingQueue = true;
		{
			_events.push_back(ae);
		}
		_accessingQueue = false;
	}

	void AudioEventQueue::copyQueue(std::vector<AudioEvent>& queue) {
		while (_accessingQueue) {}

		_accessingQueue = true;
		{
			queue = _events;
			_events.clear();
		}
		_accessingQueue = false;
	}

}
