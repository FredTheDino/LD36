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

		static std::ifstream* openFile(const std::string& path);
	};
}