#include "sound.h"
#include "sound.h"

#include "audiohandler.h"
#include "audioeventqueue.h"

#include <AL/al.h>

namespace Jam {

	Sound::Sound() {
		_source = AudioHandler::_generateSource();
		setGain(_gain);
		setPitch(_pitch);
		setLooping(_looping);
		stop();
	}

	Sound::~Sound() {
		AudioHandler::_destroySource(_source);
	}

	void Sound::fadeGain(float target, float time) {
		for (size_t i = 0; i < _fadeValues.size(); i++) {
			if (_fadeValues[i].fadeTarget == FadeTarget::GAIN) {
				_fadeValues.erase(_fadeValues.begin() + i);
				break;
			}
		}

		_fadeValues.push_back(FadeData(FadeTarget::GAIN, target, time));
	}

	void Sound::fadePitch(float target, float time) {
		for (size_t i = 0; i < _fadeValues.size(); i++) {
			if (_fadeValues[i].fadeTarget == FadeTarget::PITCH) {
				_fadeValues.erase(_fadeValues.begin() + i);
				break;
			}
		}

		_fadeValues.push_back(FadeData(FadeTarget::PITCH, target, time));
	}


	void Sound::play() {
		_sendEventOfType(AudioEventData::Type::PLAY);
		_stopped = false;
		_playing = true;
	}

	void Sound::play(const std::string & nickname) {
		stop();
		setBuffer(nickname);
		play();
	}

	void Sound::pause() {
		_sendEventOfType(AudioEventData::Type::PAUSE);
		_playing = false;
	}

	void Sound::stop() {
		_sendEventOfType(AudioEventData::Type::STOP);
		_stopped = true;
		_playing = false;
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
		_gain = gain;
	}

	void Sound::setPitch(float pitch) {
		AudioEvent ae;
		ae.source = _source;
		ae.target = AL_PITCH;
		ae.type = AudioEventData::Type::SET;
		ae.fData[0] = pitch;
		AudioEventQueue::pushDataToQueue(ae);
		_pitch = pitch;
	}

	void Sound::setLooping(bool looping) {
		AudioEvent ae;
		ae.source = _source;
		ae.target = AL_LOOPING;
		ae.type = AudioEventData::Type::SET;
		ae.iData[0] = looping;
		AudioEventQueue::pushDataToQueue(ae);
		_looping = looping;
	}

	void Sound::updateFade(double delta) {
		FadeData* data;
		std::vector<size_t> toBeDeleted;

		for (size_t i = 0; i < _fadeValues.size(); i++) {
			data = &_fadeValues[i];
			float slope = data->target / data->time;
			data->t += (float) delta;

			switch (data->fadeTarget) {
				case FadeTarget::GAIN:
					if (data->t < data->time) {
						setGain((float) _gain + slope * delta);
					} else {
						setGain(_gain);
						toBeDeleted.push_back(i);
					}
					break;
				case FadeTarget::PITCH:
					if (data->t < data->time) {
						setPitch((float) _pitch + slope * delta);
					} else {
						setPitch(_pitch);
						toBeDeleted.push_back(i);
					}
					break;
				default:
					break;
			}
		}

		//Run the for loop backwards to make sure all indexes are up to date
		for (size_t i = toBeDeleted.size(); 0 < i; i++) {
			_fadeValues.erase(_fadeValues.begin() + toBeDeleted[i]);
		}
	}

	void Sound::_sendEventOfType(AudioEventData::Type type) {
		AudioEvent ae;
		ae.source = _source;
		ae.type = type;
		AudioEventQueue::pushDataToQueue(ae);
	}

}
