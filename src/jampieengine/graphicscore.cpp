#include "graphicscore.h"

using namespace Jam;

GraphicsCore::GraphicsCore(Pie& pie, Flavor& flavor)
	: _pie(pie)
{
	
}

void GraphicsCore::_bake(Flavor& flavor)
{
	_thread = new std::thread(&GraphicsCore::_start, this);
}

void GraphicsCore::_start()
{
	_window = new Window(*this, _pie._flavor);

	while (_pie.isCooking()) {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				_pie.eat();
			}
		}
	}

	delete _window;
}

GraphicsCore::~GraphicsCore()
{
	_thread->join();
	delete _thread;
}