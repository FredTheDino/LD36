#include "audiocore.h"
#include "pie.h"

using namespace Jam;

AudioCore::AudioCore(Pie& pie, Flavor& flavor)
	: _pie(pie) {

	std::cout << alcGetString(NULL, ALC_DEVICE_SPECIFIER) << std::endl;

	_device = alcOpenDevice(NULL);
	if (!_device) 
		printf("AL Error: no audio output device\n");
		
	_context = alcCreateContext(_device, NULL);
	if (!alcMakeContextCurrent(_context)) 
		printf("AL Error: cannot create context\n");

}

void AudioCore::_bake(Flavor& flavor) {
	_thread = new std::thread(&AudioCore::_start, this);
}

void AudioCore::_start() {

	while (_pie.isCooking()) {
		
	}
}

AudioCore::~AudioCore() {
	_thread->join();

	alcCloseDevice(_device);
	alcDestroyContext(_context);
	delete _thread;
}