#include "window.h"

using namespace Jam;

Window::Window(GraphicsCore& graphicsCore, Flavor& flavor)
{
	_handle = SDL_CreateWindow(flavor.title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, flavor.w_width, flavor.w_height, SDL_WINDOW_SHOWN);
}

Window::~Window()
{
	SDL_DestroyWindow(_handle);
}