#include "audiocore.h"
#include "pie.h"

#include <vector>

using namespace Jam;

AudioCore::AudioCore(Pie& pie, Flavor& flavor)
	: _pie(pie) {

	_device = alcOpenDevice(NULL);
	if (!_device) 
		printf("AL Error: no audio output device\n");
		
	_context = alcCreateContext(_device, NULL);
	if (!alcMakeContextCurrent(_context)) 
		printf("AL Error: cannot create context\n");

	printf("[OpenAL] Version: %s\n", alGetString(AL_VERSION));
	printf("[OpenAL] Vendor: %s\n", alGetString(AL_VENDOR));
	printf("[OpenAL] Renderer: %s\n", alGetString(AL_RENDERER));

	alGenSources(1, &_source);

	_library.preload("Fred", "jungle.wav");

	alSourcei(_source, AL_BUFFER, 2);
	alSourcef(_source, AL_GAIN, 0.01);
	alSourcePlay(_source);

	/*
	//Generate a sinus wave
	float freq = 222.0;
	int time = 4;
	unsigned int sampleRate = 22050;
	size_t bufferSize = time * sampleRate;

	std::vector<short> buffer;
	buffer.resize(bufferSize);

	for (size_t i = 0; i < bufferSize; i++) {
		buffer[i] = 100 * sin((i * 2.0 * 3.14 * freq) / sampleRate);
	}

	alGenBuffers(1, &_buffer);
	alBufferData(_buffer, AL_FORMAT_MONO16, &buffer[0], bufferSize, sampleRate);
	alSourcei(_source, AL_BUFFER, _buffer);
	alSourcePlay(_source);
	*/
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

	alDeleteSources(1, &_source);
	alDeleteBuffers(1, &_buffer);
	alcCloseDevice(_device);
	alcDestroyContext(_context);
	delete _thread;
}