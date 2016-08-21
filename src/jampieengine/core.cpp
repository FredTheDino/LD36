#include "core.h"


using namespace Jam;

Core::Core(Pie& pie): _pie(pie) {
};

Core::~Core() {
}

void Jam::Core::join() {
	if (_thread->joinable()) {
		_thread->join();
	}
	delete _thread;
};