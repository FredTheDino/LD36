#pragma once

#include <unordered_map>
#include <string>
#include <cstring>
#include <typeinfo>

#include "loader.h"

namespace Jam
{
	class Loader;

	class SST
	{
	public:

		SST() {};

		template <typename T>
		void add(std::string tag, T data) { add(tag, (void*) new T(data), (unsigned char) sizeof(data)); };

		void add(std::string tag, const char* data) { add(tag, (void*) data, (unsigned char) strlen(data)); };
		void add(std::string tag, std::string data) { add(tag, (void*) dynamic_cast<std::string*>(&data)->c_str(), (unsigned char) dynamic_cast<std::string*>(&data)->length()); };

		void add(std::string tag, void* data, unsigned char size) { _saveData.insert(std::make_pair(tag, std::make_pair(data, size))); };

		template <typename T>
		void get(std::string tag, T& data) { data = *((T*) _saveData.at(tag).first); };

		void get(std::string tag, std::string& data) { data = std::string((char*) _saveData.at(tag).first, _saveData.at(tag).second); };

		void remove(std::string tag) { _saveData.erase(tag); };

		static void setEncryptionKey(unsigned char key) { _encryptionKey = key; };

	private:

		//Encryption key
		static unsigned char _encryptionKey;

		//Information is contained in the following format: <tag, <value_ptr, size>>
		std::unordered_map<std::string, std::pair<void*, unsigned char>> _saveData;

		friend Loader;
	};
}