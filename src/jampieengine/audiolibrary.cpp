#include "audiolibrary.h"

#include "loader.h"

namespace Jam {

	AudioLibrary::AudioLibrary() {
		_preloadingQueue.reserve(20);
		_unloadingQueue.reserve(20);
		_library.reserve(20);
	}

	AudioLibrary::~AudioLibrary() {
		while (_accessingLibrary) {}
		_accessingLibrary = true;
		{
			for (auto it = _library.begin(); it != _library.end(); it++) {
				alDeleteBuffers(1, &(it->second));
			}
		}
		_accessingLibrary = false;
	}

	void AudioLibrary::preload(std::string nickname, std::string path) {
		while (_accessingPreloadingQueue) {}
		_accessingPreloadingQueue = true;
		{
			_preloadingQueue.push_back(path);
			_load(path);
		}
		_accessingPreloadingQueue = false;
	}

	void AudioLibrary::unload(std::string nickname) {
		while (_accessingLibrary) {}
		_accessingLibrary = true;
		{
			auto it = _library.find(nickname);
			if (it != _library.end()) {
				alDeleteBuffers(1, &_library[nickname]);
				_library.erase(nickname);
			}
		}
		_accessingLibrary = false;
	}

	bool AudioLibrary::ready() {
		return false;
	}

	void AudioLibrary::update() {}

	void AudioLibrary::_load(std::string path) {

		ALuint bufferID = 0;
		alGenBuffers(1, &bufferID);

		std::vector<char> buffer = Loader::loadCharBuffer(path);

		//Read in header
		//Make sure it's a wave file
		if (!(buffer[8] == 'W' && buffer[9] == 'A' && buffer[10] == 'V' && buffer[11] == 'E')) {
			std::cout << path << " is not a .wave file." << std::endl;
			return;
		}

		//Make sure it isn't compressed
		if (1 != ((buffer[20] << 0x0) | (buffer[21] << 0x8))) {
			std::cout << path << " is compressed." << std::endl;
			return;
		}

		//Get the number of channels
		unsigned short numChannels = buffer[22] << 0x0 | buffer[23] << 0x8;
		
		//Get the sample rate
		unsigned int sampleRate =
			(( (unsigned char) buffer[24]) << 0x0) | 
			(( (unsigned char) buffer[25]) << 0x8) |
			(( (unsigned char) buffer[26]) << 0x10) |
			(( (unsigned char) buffer[27]) << 0x18);
		
		//The bits for each sample 68 -84
		unsigned short bitsPerSample = buffer[34] << 0x0 | buffer[35] << 0x8;

		//Find out which format it is
		ALenum format;
		if (numChannels == 1) {
			if (bitsPerSample == 8) {
				format = AL_FORMAT_MONO8;
			} else {
				format = AL_FORMAT_MONO16;
			}
		} else {
			if (bitsPerSample == 8) {
				format = AL_FORMAT_STEREO8;
			} else {
				format = AL_FORMAT_STEREO16;
			}
		}

		printf("numChanels: %i\nsampleRate: %i\nbitsPerSample: %i\n", numChannels, sampleRate, bitsPerSample);

		//Load it to the buffer
		alBufferData(bufferID, format, &buffer[44], buffer.size() - 44, sampleRate);
		std::cout << bufferID << std::endl;
	}
}