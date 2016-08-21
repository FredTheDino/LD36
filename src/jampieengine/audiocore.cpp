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

	_ready = true;

	while (_pie.isCooking()) {
		AudioHandler::update();
		Time::wait();
	}

	Time::unregisterThread();
}

AudioCore::~AudioCore() {}