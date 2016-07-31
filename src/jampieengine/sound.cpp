#include "sound.h"

#include "audiohandler.h"
#include "audioeventqueue.h"

#include <AL/al.h>

namespace Jam {

	Sound::Sound() {
		_source = AudioHandler::_generateSource();
	}

	Sound::~Sound() {
		AudioHandler::_destroySource(_source);
	}

	void Sound::play() {
		_sendEventOfType(AudioEventData::Type::PLAY);
	}

	void Sound::play(const std::string & nickname) {
		stop();
		setBuffer(nickname);
		play();
	}

	void Sound::pause() {
		_sendEventOfType(AudioEventData::Type::PAUSE);
	}

	void Sound::stop() {
		_sendEventOfType(AudioEventData::Type::STOP);
	}

	void Sound::rewind() {
		_sendEventOfType(AudioEventData::Type::REWIND);
	}

	void Sound::queue(const std::string & nickname) {
		_sendEventOfType(AudioEventData::Type::QUEUE);
	}

	void Sound::clearQueue() {
		_sendEventOfType(AudioEventData::Type::CLEAR_QUEUE);
	}

	void Sound::setBuffer(const std::string & nickname) {
		AudioEvent ae;
		ae.source = _source;
		ae.target = AL_BUFFER;
		ae.type = AudioEventData::Type::SET;
		ae.nickname = nickname;
		AudioEventQueue::pushDataToQueue(ae);
	}

	void Sound::setGain(float gain) {
		AudioEvent ae;
		ae.source = _source;
		ae.target = AL_GAIN;
		ae.type = AudioEventData::Type::SET;
		ae.fData[0] = gain;
		AudioEventQueue::pushDataToQueue(ae);
	}

	void Sound::setPitch(float pitch) {
		AudioEvent ae;
		ae.source = _source;
		ae.target = AL_PITCH;
		ae.type = AudioEventData::Type::SET;
		ae.fData[0] = pitch;
		AudioEventQueue::pushDataToQueue(ae);
	}

	void Sound::setLooping(bool looping) {
		AudioEvent ae;
		ae.source = _source;
		ae.target = AL_LOOPING;
		ae.type = AudioEventData::Type::SET;
		ae.iData[0] = looping;
		AudioEventQueue::pushDataToQueue(ae);
	}

	void Sound::_sendEventOfType(AudioEventData::Type type) {
		AudioEvent ae;
		ae.source = _source;
		ae.type = type;
		AudioEventQueue::pushDataToQueue(ae);
	}

}
