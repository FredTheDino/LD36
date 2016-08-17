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

	_graphicsCore->_bake(_flavor);
	_soundCore->_bake(_flavor);

	_gameStateManager = new GameStateManager(*this, GameStateLibrary::getGameState(_flavor.enterState));

	InputHandler::init(_flavor);

	Time::registerThread();

	while (_cooking) {
		InputHandler::update();
		_gameStateManager->update(Time::getDelta());
		Time::wait();
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	_soundCore->join();
	_graphicsCore->join();

	Time::unregisterThread();

	InputHandler::destroy();

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
	_soundCore = new AudioCore(*this, _flavor);
}

Pie::~Pie()
{
	delete _graphicsCore;
	delete _soundCore;
	SDL_Quit();
}