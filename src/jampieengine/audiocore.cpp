#include "audiocore.h"
#include "pie.h"
#include "audiohandler.h"

#include <vector>
#include <chrono>

#include "sound.h"
#include "spatialsound.h"

using namespace Jam;

AudioCore::AudioCore(Pie& pie, Flavor& flavor)
	: _pie(pie) {
	AudioHandler::init(_library);

	AudioHandler::preload("fred", "jungle.wav");
	AudioHandler::preload("test", "audio.wav");
}

void AudioCore::_bake(Flavor& flavor) {
	_thread = new std::thread(&AudioCore::_start, this);
}

void AudioCore::_start() {

	bool isReady = false;

	SpatialSound ssound;
	Sound sound;

	while (_pie.isCooking()) {
		_library.update();
		AudioHandler::update();

		if (_library.ready()) {
			if (!isReady) {
				sound.setBuffer("fred");
				sound.setGain(0.02);
				sound.setPitch(1);
				sound.setLooping(true);
				//sound.play();

				ssound.play("test");
				ssound.setLooping(true);
				ssound.setGain(0.2);
				ssound.setPosition(-10, -2, -2);
				ssound.setVelocity(10, 2, 2);
			}

			isReady = true;
		}
	}
}

AudioCore::~AudioCore() {
	_thread->join();
	delete _thread;
}