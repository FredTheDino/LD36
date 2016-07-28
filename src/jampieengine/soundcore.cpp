#include "soundcore.h"
#include "pie.h"

using namespace Jam;

SoundCore::SoundCore(Pie& pie, Flavor& flavor)
	: _pie(pie) {

}

void SoundCore::_bake(Flavor& flavor) {
	_thread = new std::thread(&SoundCore::_start, this);
}

void SoundCore::_start() {

	while (_pie.isCooking()) {
		
	}
}

SoundCore::~SoundCore() {
	_thread->join();
	delete _thread;
}