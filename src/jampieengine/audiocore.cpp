#include "pie.h"
#include "audiocore.h"
#include "audiohandler.h"

#include <vector>
#include <chrono>

#include "sound.h"
#include "spatialsound.h"
#include "audiolistener.h"

using namespace Jam;

AudioCore::AudioCore(Pie& pie, Flavor& flavor)
	: Core(pie) {
	AudioHandler::init(_library);

	AudioHandler::preload("fred", "jungle.wav");
	AudioHandler::preload("test", "audio.wav");
}

void AudioCore::_bake(Flavor& flavor) {
	_thread = new std::thread(&AudioCore::_start, this);
}

void AudioCore::_start() {

	Time::registerThread();

	bool isReady = false;

	SpatialSound ssound;
	Sound sound;

	AudioListener::setPosition(glm::vec3(-10, -2, -2));

	while (_pie.isCooking()) {
		Time::update();
		_library.update();
		AudioHandler::update();
		/*
		if (_library.ready()) {
			if (!isReady) {
				sound.setBuffer("fred");
				sound.setGain(0.04f);
				sound.setPitch(1);
				sound.setLooping(true);
				//sound.play();

				ssound.play("test");
				ssound.setLooping(true);
				ssound.setGain(0.2f);
				ssound.setPosition(-10, -2, -2);
				ssound.setVelocity(10, 2, 2);
			}

			isReady = true;
		}*/
		Time::wait();
	}

	Time::unregisterThread();
}

AudioCore::~AudioCore() {
	_thread->join();
	delete _thread;
}