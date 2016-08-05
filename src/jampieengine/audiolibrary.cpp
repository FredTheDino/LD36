#include "audiolibrary.h"

#include "loader.h"

namespace Jam {

	namespace Helper {
		unsigned int getInt(std::vector<char>& buffer, size_t index) {
			unsigned int temp = 0;

			temp |= (((unsigned char) buffer[index++]) << 0x0);
			temp |= (((unsigned char) buffer[index++]) << 0x8);
			temp |= (((unsigned char) buffer[index++]) << 0x10);
			temp |= (((unsigned char) buffer[index]) << 0x18);

			return temp;
		}

		unsigned short getShort(std::vector<char>& buffer, size_t index) {
			unsigned short temp = 0;

			temp |= (((char) buffer[index++]) << 0x0);
			temp |= (((char) buffer[index]) << 0x8);

			return temp;
		}
	}

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
			_ready = false;
			_preloadingQueue.insert(std::make_pair(nickname, path));
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

	ALuint AudioLibrary::operator[](const std::string & nickname) {
		ALuint buffer = 0;

		while (_accessingLibrary) {};
		_accessingLibrary = true;
		{
			auto it = _library.find(nickname);
			if (it != _library.end())
				buffer = it->second;
		}
		_accessingLibrary = false;

		return buffer;
	}

	bool AudioLibrary::ready() {
		return _ready;
	}

	void AudioLibrary::update() {
		//Check if we are loading
		if (_ioThread) {
			//If we are, is it done?
			if (_ioThread->joinable()) {
				//If it is, join
				_ioThread->join();
				delete _ioThread;
				_ioThread = nullptr;
			} else {
				//Else there's nothing to do
				return;
			}
		}

		while (_accessingPreloadingQueue) {};
		//We can load something
		_accessingPreloadingQueue = true;
		//Is there something to load
		if (0 != _preloadingQueue.size()) {
			auto it = _preloadingQueue.begin();
			_ioThread = new std::thread(&AudioLibrary::_load, this, it->first, it->second);
			_preloadingQueue.erase(it->first);
		} else {
			//Then we're ready to rock!
			_ready = true;
		}
		_accessingPreloadingQueue = false;
	}

	

	void AudioLibrary::_load(std::string nickname, std::string path) {

		//Load the file
		std::vector<char> buffer = Loader::loadCharBuffer(path);

		//Make sure it's a wave file and find the fmt chunk
		size_t currentAddress = 0;
		size_t maxHeaderSize = 512;
		while (currentAddress < maxHeaderSize) {
			if (buffer[currentAddress++] != 'f') continue;
			if (buffer[currentAddress++] != 'm') continue;
			if (buffer[currentAddress++] != 't') continue;
			if (buffer[currentAddress++] != ' ') continue;
			break;
		}

		//Check if it was found
		if (maxHeaderSize <= currentAddress) {
			std::cout << path << "is not of type wav" << std::endl;
			return;
		}

		//Make sure it isn't compressed
		short compression = Helper::getShort(buffer, currentAddress + 4);
		if (1 != compression) {
			std::cout << path << " is compressed." << std::endl;
			return;
		}

		//Get the number of channels
		unsigned short numChannels = Helper::getShort(buffer, currentAddress + 6);//  buffer[22] << 0x0 | buffer[23] << 0x8;
		
		//Get the sample rate
		unsigned int sampleRate = Helper::getInt(buffer, currentAddress + 8);
		
		//The bits for each sample 68 -84
		unsigned short bitsPerSample = Helper::getShort(buffer, currentAddress + 18); //buffer[34] << 0x0 | buffer[35] << 0x8;

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

		//Find the data chunk
		while (currentAddress < maxHeaderSize) {
			if (buffer[currentAddress++] != 'd') continue;
			if (buffer[currentAddress++] != 'a') continue;
			if (buffer[currentAddress++] != 't') continue;
			if (buffer[currentAddress++] != 'a') continue;
			break;
		}

		//Check if it was found
		if (maxHeaderSize <= currentAddress) {
			std::cout << "Can't find the wav data for file" << path << std::endl;
			return;
		}

		//Get the size of the data
		unsigned int size = Helper::getInt(buffer, currentAddress);

		//Move it forward so we're on the actual data
		currentAddress += 4;

		//Hacky way to make sure all the data that is specified exists
		buffer[currentAddress + size - 1];

		//Generate the buffer so we don't have to clean up if the sound doesn't load
		ALuint bufferID = 0;
		alGenBuffers(1, &bufferID);

		//Load the data to the buffer
		alBufferData(bufferID, format, &buffer[currentAddress], size, sampleRate);
		
		_accessingLibrary = true;
		_library.insert(std::make_pair(nickname, bufferID));
		_accessingLibrary = false;
	}
}