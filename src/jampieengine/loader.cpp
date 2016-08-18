#include "loader.h"
#include "debug.h"

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

std::vector<char> Jam::Loader::loadCharBuffer(std::string path) {
	//Open file
	std::fstream* file = openFile(path);

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

int Jam::Loader::remove(std::string path) {
	return std::remove((prefix + path).c_str());
}

std::fstream* Loader::openFile(const std::string& path, std::ios_base::openmode mode) {
	//Open file
	std::fstream* file = new std::fstream;

	file->open(((prefix + path).c_str()), mode);

	//Make sure the file exists
	if (!file->is_open()) {
		std::string error = "Can't open file: " + path;
		Debug::err(error.c_str(), 1);
		return nullptr;
	}

	return file;
}