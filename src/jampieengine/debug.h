#pragma once

#include <iostream>
#include "SDL2/SDL_messagebox.h"

namespace Jam
{
	namespace Debug
	{
		//Error crash function
		void err(std::string msg, int err);
	}
}