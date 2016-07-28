#include "eventqueue.h"

using namespace Jam;

std::vector<SDL_Event> EventQueue::_queue;
bool EventQueue::_queueIsUsed;

void EventQueue::pushEventToQueue(SDL_Event e) {
	while (_queueIsUsed) {}
	_queueIsUsed = true;
	_queue.push_back(e);
	_queueIsUsed = false;
}

void EventQueue::copyEventQueue(std::vector<SDL_Event>* target) {
	while (_queueIsUsed) {}
	_queueIsUsed = true;
	*target = _queue;
	_queue.clear();
	_queueIsUsed = false;
}
