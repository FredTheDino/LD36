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

	_renderEngine = new RenderEngine(*_window, _pie._flavor.graphicsCoreType);

	while (_pie.isCooking()) {

		//Handle events
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
				case SDL_QUIT:
				{
					_pie.eat();
					break;
				}
				//Input handleing (BEGIN)
				case SDL_KEYDOWN:
				case SDL_KEYUP:
				case SDL_CONTROLLERBUTTONDOWN:
				case SDL_CONTROLLERBUTTONUP:
				case SDL_CONTROLLERAXISMOTION:
				case SDL_CONTROLLERDEVICEADDED:
				case SDL_CONTROLLERDEVICEREMOVED:
					InputHandler::pushEventToQueue(e);
					break;
				default:
				{
					//std::cout << "Type: " << e.type << std::endl;
					break;
				}
			}
		}

		//Draw
		_renderEngine->_draw();
	}

	delete _renderEngine;

	delete _window;
}

GraphicsCore::~GraphicsCore()
{
	_thread->join();
	delete _thread;
}
