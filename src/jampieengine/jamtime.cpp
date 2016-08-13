#include "jamtime.h"

#include <thread>

using namespace Jam;

typedef std::chrono::high_resolution_clock CLOCK;

std::vector<std::thread::id> Time::_registerdThreads;
std::vector<bool> Time::_readyThreads;
double Time::_delta = 0.0;
std::chrono::high_resolution_clock::time_point Time::_nextFrame;
std::chrono::duration<long, std::nano> Time::_desiredDelta(0);
bool Time::_accessingDesiredDelta = false;
bool Time::_accessingNextFrame = false;
bool Time::_accessingRegisterdThreads = false;
bool Time::_accessingReadyThreads = false;

void Time::registerThread() {
	while (_accessingRegisterdThreads) {}
	_accessingRegisterdThreads = true;
	while (_accessingReadyThreads) {}
	_accessingReadyThreads = true;

	//Add a new element to the list
	_registerdThreads.push_back(std::this_thread::get_id());
	_readyThreads.push_back(false);

	_accessingReadyThreads = false;
	_accessingRegisterdThreads = false;
}

void Time::unregisterThread() {
	std::thread::id id = std::this_thread::get_id();
	size_t target = -1;

	while (_accessingRegisterdThreads) {}
	_accessingRegisterdThreads = true;
	while (_accessingReadyThreads) {}
	_accessingReadyThreads = true;

	//Add a new element to the list
	for (size_t i = 0; i < _registerdThreads.size(); i++) {
		if (_registerdThreads[i] == id) {
			target = i;
		}
	}
	_registerdThreads.erase(_registerdThreads.begin() + target);
	_readyThreads.erase(_readyThreads.begin() + target);

	_accessingReadyThreads = false;
	_accessingRegisterdThreads = false;
}

void Time::update() {

	//Copy this exact point in time and use it for all calculations
	static std::chrono::high_resolution_clock::time_point now = CLOCK::now();
	static std::chrono::high_resolution_clock::time_point lastNow = CLOCK::now();
	
	now = CLOCK::now();

	while (_accessingDesiredDelta) {}
	_accessingDesiredDelta = true;
	{
		while (_accessingNextFrame) {}
		_accessingNextFrame = true;
		{
			_nextFrame = now + _desiredDelta;
		}
		_accessingNextFrame = false;
	}
	_accessingDesiredDelta = false;

	std::chrono::duration<double> chronoDelta = now - lastNow;
	_delta = chronoDelta.count();

	static double counter = 0;
	static unsigned frames = 0;

	frames++;
	counter += _delta;

	if (1.0 < counter) {
		counter = 0;
		printf("FPS: %i\n", frames);
		frames = 0;
	}

	lastNow = now;
}

void Time::setFPS(int fps) {
	//Convert from a frequency to nano seconds 
	
	if (fps != 0) {
		unsigned int temp = (unsigned int) (1.0 / ((double) fps) * 1000000000) - 1;
		std::chrono::duration<long, std::nano> newDelta(temp);

		while (_accessingDesiredDelta) {}
		_accessingDesiredDelta = true;
		_desiredDelta = newDelta;
		_accessingDesiredDelta = false;

	} else {
		std::chrono::duration<long, std::nano> newDelta(0);

		while (_accessingDesiredDelta) {}
		_accessingDesiredDelta = true;
		_desiredDelta = newDelta;
		_accessingDesiredDelta = false;
	}

}

void Time::wait() {
	/*
	//A flag to say wether or not the threads can continue
	static bool waitForThread = false;

	//Check in all threads
	while (_accessingRegisterdThreads) {}
	_accessingRegisterdThreads = true;
	{
		for (size_t i = 0; i < _registerdThreads.size(); i++) {
			if (std::this_thread::get_id() == _registerdThreads[i]) {
				while (_accessingReadyThreads) {}
				_accessingReadyThreads = true;
				{
					_readyThreads[i] = true;
					bool allReady = true;
					for (size_t j = 0; j < _readyThreads.size(); j++) {
						if (!_readyThreads[j]) {
							allReady = false;
							break;
						}
					}
					waitForThread = !allReady;
				}
				_accessingReadyThreads = false;
				break;
			}
		}
	}
	_accessingRegisterdThreads = false;
	*/

	while (_accessingNextFrame) {}
	_accessingNextFrame = true;
	//Get the current time
	std::chrono::time_point<std::chrono::high_resolution_clock> now = CLOCK::now();
	std::chrono::duration<long, std::nano> timeToSleep = (_nextFrame - now);
	_accessingNextFrame = false;
	//Decrease it a bit, to make sure we don't over sleep
	//timeToSleep -= std::chrono::nanoseconds(1000000);

	now = CLOCK::now();
	//Sleep if you have the time to spare
	if (0.0 < timeToSleep.count()) {
		//Sleep until an approximation of the next frame
		std::this_thread::sleep_for(timeToSleep);
	}

	/*
	//A signal that stops all threads in their tracks
	while (waitForThread) {}

	//Check out all threads
	while (_accessingRegisterdThreads) {}
	_accessingRegisterdThreads = true;
	{
		for (size_t i = 0; i < _registerdThreads.size(); i++) {
			if (std::this_thread::get_id() == _registerdThreads[i]) {
				while (_accessingReadyThreads) {}
				_accessingReadyThreads = true;
				{
					_readyThreads[i] = false;
				}
				_accessingReadyThreads = false;
				break;
			}
		}
	}
	_accessingRegisterdThreads = false;
	*/
}

double Jam::Time::getDelta() {
	return _delta;
}

