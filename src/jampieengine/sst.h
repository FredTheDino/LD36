#pragma once

#include <unordered_map>
#include <string>
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
		void add(std::string tag, T data) { _saveData.insert(std::make_pair(tag, std::make_pair((void*) new T(data), (unsigned char) sizeof(data)))); };

		void add(std::string tag, const char* data) { _saveData.insert(std::make_pair(tag, std::make_pair((void*) data, (unsigned char) strlen(data)))); };
		void add(std::string tag, std::string data) { _saveData.insert(std::make_pair(tag,
			std::make_pair((void*) dynamic_cast<std::string*>(&data)->c_str(),(unsigned char) dynamic_cast<std::string*>(&data)->length()))); };

		template <typename T>
		T get(std::string tag) { return *((T*) _saveData.at(tag)); };

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