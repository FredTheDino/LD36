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

		std::string getTitle() { return std::string(SDL_GetWindowTitle(_handle)); };

		void getSize(int* w, int* h) { SDL_GetWindowSize(_handle, w, h); };

		float getAspectRatio() { int w; int h; getSize(&w, &h); return ((float) w) / ((float) h); };

		SDL_Window* getHandle() { return _handle; };

	private:
		SDL_Window* _handle;

	};
}