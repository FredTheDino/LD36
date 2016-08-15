#include "pie.h"

using namespace Jam;

Pie::Pie(Flavor& flavor)
	: _flavor(flavor)
{
	_initSDL();
	_initCores();
}

void Pie::bake()
{
	_cooking = true;

	Time::registerThread();

	_graphicsCore->_bake(_flavor);
	_logicCore->_bake(_flavor);
	_soundCore->_bake(_flavor);

	_gameStateManager = new GameStateManager(*this);

	Time::registerThread();

	while (_cooking) {
		_gameStateManager->update();
		Time::wait();
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	_soundCore->join();
	_logicCore->join();
	_graphicsCore->join();

	Time::unregisterThread();

	delete _gameStateManager;
}

void Pie::_initSDL()
{
	int error = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS | SDL_INIT_JOYSTICK);

	if (error < 0) {
		Debug::err(SDL_GetError(), error);
	}
}

void Pie::_initCores()
{
	_graphicsCore = new GraphicsCore(*this, _flavor);
	_logicCore = new LogicCore(*this, _flavor);
	_soundCore = new AudioCore(*this, _flavor);
}

Pie::~Pie()
{
	delete _graphicsCore;
	delete _logicCore;
	delete _soundCore;
	SDL_Quit();
}