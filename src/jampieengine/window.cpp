#include "window.h"

using namespace Jam;

Window::Window(GraphicsCore& graphicsCore, Flavor& flavor)
{
	_handle = SDL_CreateWindow(flavor.title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, flavor.w_width, flavor.w_height, SDL_WINDOW_SHOWN
		| ((flavor.graphicsCoreType == GRAPHICS_TYPE_OPENGL) * SDL_WINDOW_OPENGL) //Using OpenGL?
		| ((!flavor.w_border) * SDL_WINDOW_BORDERLESS) //Borderless?
	);
}

Window::~Window()
{
	SDL_DestroyWindow(_handle);
}