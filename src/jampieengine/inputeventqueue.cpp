#include "inputeventqueue.h"

using namespace Jam;

std::vector<SDL_Event> InputEventQueue::_queue;
bool InputEventQueue::_queueIsUsed;

void InputEventQueue::pushEventToQueue(SDL_Event e) {
	while (_queueIsUsed) {}
	_queueIsUsed = true;
	_queue.push_back(e);
	_queueIsUsed = false;
}

void InputEventQueue::copyEventQueue(std::vector<SDL_Event>* target) {
	while (_queueIsUsed) {}
	_queueIsUsed = true;
	*target = _queue;
	_queue.clear();
	_queueIsUsed = false;
}
