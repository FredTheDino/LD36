#include "audiohandler.h"

#include "audioeventqueue.h"
#include "audioevent.h"
#include "audiolibrary.h"

#include <AL/al.h>
#include <AL/alc.h>

namespace Jam {

	ALCdevice* AudioHandler::_device = nullptr;
	ALCcontext* AudioHandler::_context = nullptr;
	AudioLibrary* AudioHandler::_library = nullptr;

	std::vector<ALuint> AudioHandler::_sources;
	bool AudioHandler::_accessingSource = false;

	void AudioHandler::init(AudioLibrary& library) {

		_library = &library;

		_device = alcOpenDevice(NULL);
		if (!_device)
			printf("AL Error: no audio output device\n");

		_context = alcCreateContext(_device, NULL);
		if (!alcMakeContextCurrent(_context))
			printf("AL Error: cannot create context\n");

		printf("[OpenAL] Version: %s\n", alGetString(AL_VERSION));
		printf("[OpenAL] Vendor: %s\n", alGetString(AL_VENDOR));
		printf("[OpenAL] Renderer: %s\n", alGetString(AL_RENDERER));
	}

	void AudioHandler::destroy() {
		for (size_t i = 0; i < _sources.size(); i++) {
			if (_sources[i] != 0)
				alDeleteSources(1, &_sources[i]);
		}

		alcCloseDevice(_device);
		alcDestroyContext(_context);
	}

	void AudioHandler::update() {
		AudioEvent e;
		std::vector<AudioEvent> events;

		_library->update();
		
		{
			while(AudioEventQueue::_accessingQueue) {}
			AudioEventQueue::_accessingQueue = true;
			
			events = AudioEventQueue::_events;
			AudioEventQueue::_events.clear();
			
			AudioEvent ae;
			ae.type = AudioEventData::Type::DUMMY;
			AudioEventQueue::_events.push_back(ae);
			
			AudioEventQueue::_accessingQueue = false;
		}

		//std::cout << events.size() << std::endl;

		for (size_t i = 0; i < events.size(); i++) {
			e = events[i];
			switch (e.type) {
				case AudioEventData::Type::PLAY:
					alSourcePlay(e.source);
					break;
				case AudioEventData::Type::PAUSE:
					alSourcePause(e.source);
					break;
				case AudioEventData::Type::STOP:
					alSourceStop(e.source);
					break;
				case AudioEventData::Type::REWIND:
					alSourceRewind(e.source);
					break;
				case AudioEventData::Type::QUEUE: 
				{
					ALuint b = e.iData[0];
					alSourceQueueBuffers(e.source, 1, &b);
					break;
				}
				case AudioEventData::Type::CLEAR_QUEUE:
				{
					ALint numBuffers = 0;
					alGetSourcei(e.source, AL_BUFFERS_QUEUED, &numBuffers);
					alSourceUnqueueBuffers(e.source, numBuffers, NULL);
					break;
				}
				case AudioEventData::Type::SET:
					_set(e);
					break;

				case AudioEventData::Type::LISTENER:
					_listener(e);
					break;
				default:
					break;
			}
		}
	}

	void AudioHandler::preload(const std::string& nickname, const std::string& path) {
		_library->preload(nickname, path);
	}

	void AudioHandler::unload(const std::string& nickname) {
		_library->unload(nickname);
	}

	bool AudioHandler::ready() {
		return _library->ready();
	}

	ALuint AudioHandler::_generateSource() {
		ALuint source;
		alGenSources(1, &source);

		while (_accessingSource) {};
		_accessingSource = true;
		{
			size_t i = -1;
			for (; i < _sources.size(); i++) {
				if (_sources[i] == 0)
					break;
			}
			if (i == -1)
				_sources.push_back(source);
			else {
				_sources.push_back(source);
			}
		}
		_accessingSource = false;
		
		return source;
	}

	void AudioHandler::_destroySource(ALuint source) {
		while (_accessingSource) {};
		_accessingSource = true;
		{
			for (size_t i = 0; i < _sources.size(); i++) {
				if (_sources[i] == source) {
					alDeleteSources(1, &source);
					_sources[i] = 0;
				}
			}
		}
		_accessingSource = false;
	}

	void AudioHandler::_set(AudioEvent& e) {
		
		switch (e.target) {
			case AL_PITCH:
			case AL_GAIN:
			case AL_MIN_GAIN:
			case AL_MAX_GAIN:
			case AL_ROLLOFF_FACTOR:
			case AL_REFERENCE_DISTANCE:
				alSourcef(e.source, e.target, e.fData[0]);
				break;
			case AL_VELOCITY:
			case AL_DIRECTION:
			case AL_POSITION:
				alSourcefv(e.source, e.target, e.fData);
				break;
			case AL_LOOPING:
			{
				ALenum value;

				if (e.iData[0] == 0) {
					value = AL_FALSE;
				} else {
					value = AL_TRUE;
				}

				alSourcei(e.source, e.target, value);
				break;
			}
			case AL_BUFFER:
				alSourcei(e.source, e.target, (*_library)[e.nickname]);
				break;
			default:
				break;
		}
	}

	void AudioHandler::_listener(AudioEvent & e) {

		switch (e.target) {
			case AL_GAIN:
				alListenerf(e.target, e.fData[0]);
				break;
			case AL_VELOCITY:
			case AL_DIRECTION:
			case AL_POSITION:
				alListenerfv(e.target, e.fData);
				break;
			default:
				break;
		}
	}
}