#include "loader.h"
#include "debug.h"

#include <string>

using namespace Jam;

std::string Loader::prefix("");

std::string Loader::loadText(std::string path)
{
	//Open file
	std::fstream* file = openFile(path);

	//Determine length of file
	file->seekg(0, file->end);
	size_t size = file->tellg();

	//Create string with file size
	std::string buffer(size, ' ');

	//Read file
	file->seekg(0, file->beg);
	file->read(&buffer[0], size);

	//Close file
	file->close();
	delete file;

	return buffer;
}

std::vector<char> Jam::Loader::loadCharBuffer(std::string path)
{
	//Open file
	std::fstream* file = openFile(path, std::ios::binary | std::ios::in);

	//Determine length of file
	file->seekg(0, file->end);
	size_t size = file->tellg();

	//Create a buffer to load the char data into
	std::vector<char> buffer(size, ' ');

	//Copy file
	file->seekg(0, file->beg);
	file->read(&buffer[0], size);

	//Close file
	file->close();
	delete file;

	return buffer;
}

int Jam::Loader::remove(std::string path)
{
	return std::remove((prefix + path).c_str());
}

SST Jam::Loader::loadSST(std::string path)
{
	Jam::SST sst;

	std::fstream* file = openFile(path, std::ios::in | std::ios::binary);

	//Determine file size
	file->seekg(0, file->end);
	size_t size = file->tellg();

	//Reset marker
	file->seekg(0, file->beg);
	unsigned int offset = 0;
	while (offset < size) {

		//Read tag length
		unsigned char tagLength;
		file->read((char*) &tagLength, 1);
		offset++;

		//Decrypt tag length
		tagLength ^= SST::_encryptionKey;

		//Read tag
		std::vector<unsigned char> tag(tagLength);
		file->read((char*) tag.data(), tagLength);
		offset += tagLength;

		//Decrypt tag
		for (unsigned int i = 0; i < tag.size(); i++) {
			tag[i] ^= SST::_encryptionKey;
		}

		//Read data length
		unsigned char dataLength;
		file->read((char*) &dataLength, 1);
		offset++;

		//Decrypt data length
		dataLength ^= SST::_encryptionKey;

		//Read data
		std::vector<unsigned char> data(dataLength);
		file->read((char*) data.data(), dataLength);
		offset += dataLength;


		//Decrypt data
		for (unsigned int i = 0; i < data.size(); i++) {
			data[i] ^= SST::_encryptionKey;
		}

		//Copy data to heap (currently transient)
		void* raw = malloc(dataLength);
		memcpy(raw, (void*) data.data(), dataLength);

		sst.add(std::string((char*) tag.data(), tagLength), raw, dataLength);
	}

	file->close();
	delete file;

	return sst;
}

void Jam::Loader::saveSST(SST& data, std::string path)
{
	std::fstream* file = openFile(path, std::ios::out | std::ios::binary, true);

	for (std::pair<std::string, std::pair<void*, unsigned char>> tag : data._saveData) {

		//Encrypted length of tag
		unsigned char tagLength = tag.first.length() ^ SST::_encryptionKey;
		
		//Tag vector
		std::vector<unsigned char> d_tag((const char*) tag.first.c_str(), ((const char*) tag.first.c_str()) + tag.first.length());
		
		//Encrypting tag vector
		for (unsigned int i = 0; i < d_tag.size(); i++) {
			d_tag[i] ^= SST::_encryptionKey;
		}

		//Encrypted length of data
		unsigned char dataLength = tag.second.second ^ SST::_encryptionKey;

		//Data vector
		std::vector<unsigned char> d_data(((unsigned char*) tag.second.first), ((unsigned char*) tag.second.first) + tag.second.second);

		//Encrypting data vector
		for (unsigned int i = 0; i < d_data.size(); i++) {
			d_data[i] ^= SST::_encryptionKey;
		}

		//Write tag
		file->write((char*) &tagLength, 1); //Size of tag name
		file->write((char*) d_tag.data(), d_tag.size()); //Tag name


		//Write data
		file->write((char*) &dataLength, 1); //Size of data
		file->write((char*) d_data.data(), tag.second.second); //Data
	}

	file->close();
	delete file;
}

std::fstream* Loader::openFile(const std::string& path, std::ios_base::openmode mode, bool create)
{
	//Open file
	std::fstream* file = new std::fstream;

	file->open(((prefix + path).c_str()), mode);

	//Make sure the file exists
	if (!file->is_open() && !create) {
		std::string error = "Can't open file: " + path;
		Debug::err(error.c_str(), 1);
		return nullptr;
	}

	return file;
}