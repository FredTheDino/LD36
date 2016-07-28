#pragma once

#include <iostream>
#include <string>
#include <fstream>



namespace Jam
{
	class Loader
	{
	public:
		static std::string prefix;
		static std::string loadText(std::string path);
	};
}