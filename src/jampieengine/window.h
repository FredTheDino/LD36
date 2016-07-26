#pragma once

#include "SDL2/SDL.h"

#include "graphicscore.h"

namespace Jam
{
	//Forward declarations
	class GraphicsCore;
	struct Flavor;

	class Window
	{
	public:
		Window(GraphicsCore& graphicsCore, Flavor& flavor);
		~Window();

	private:
		SDL_Window* _handle;

	};
}