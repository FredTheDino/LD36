#pragma once

#include <iostream>
#include "SDL2/SDL_messagebox.h"

namespace Jam
{
	namespace Debug
	{
		//Error crash function
		void err(const char* msg, int err);
	}
}