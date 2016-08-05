#include "loader.h"
#include "debug.h"

using namespace Jam;

std::string Loader::prefix("");

std::string Loader::loadText(std::string path)
{
	//Create full path
	std::string fullPath = prefix + path;

	//Open file
	std::ifstream file(
		fullPath, 
		std::ifstream::binary);

	//Make sure the file exists
	if (!file.is_open()) {
		std::string error = "Can't open file: " + path;
		Debug::err(error.c_str(), 1);
	}
	

	//Determine length of file
	//file.seekg(0, std::ios::end);
	file.seekg(0, file.end);
	size_t size = file.tellg();
	

	//Create string with file size
	std::string buffer(size, ' ');

	//Read file
	file.seekg(0, file.beg);
	file.read(&buffer[0], size);

	//Close file
	file.close();

	return buffer;
}