#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

namespace Jam
{
	class Loader
	{
	public:
		static std::string prefix;
		static std::string loadText(std::string path);
		static std::vector<char> loadCharBuffer(std::string path);
		static int remove(std::string path);

		static std::fstream* openFile(const std::string& path, std::ios_base::openmode mode = std::ios_base::in);
	};
}