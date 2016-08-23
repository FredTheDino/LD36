#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "sst.h"

namespace Jam
{
	class SST;

	class Loader
	{
	public:
		static std::string prefix;
		static std::string loadText(std::string path);
		static std::vector<char> loadCharBuffer(std::string path);
		static int remove(std::string path);

		//SST
		static SST loadSST(std::string path);
		static void saveSST(SST& data, std::string path);

		static std::fstream* openFile(const std::string& path, std::ios_base::openmode mode = std::ios_base::in, bool create = false);
	};
}