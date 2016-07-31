#include "graphicscore.h"
#include "inputeventqueue.h"

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
				
				case SDL_CONTROLLERDEVICEADDED:
				{
#ifdef _DEBUG
					std::cout << "Device added." << std::endl;
#endif
					InputHandler::controllerConnectionEvent(true, e.cdevice.which);
					break;
				}
				case SDL_CONTROLLERDEVICEREMOVED:
				{
#ifdef _DEBUG
					std::cout << "Device removed." << std::endl;
#endif
					InputHandler::controllerConnectionEvent(false, e.cdevice.which);
					break;
				}

				//Input handleing
				case SDL_KEYDOWN:
				case SDL_KEYUP:
				case SDL_CONTROLLERBUTTONDOWN:
				case SDL_CONTROLLERBUTTONUP:
				case SDL_MOUSEBUTTONDOWN:
				case SDL_MOUSEBUTTONUP:
				case SDL_CONTROLLERAXISMOTION:
				case SDL_MOUSEMOTION:
					InputEventQueue::pushEventToQueue(e);
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
