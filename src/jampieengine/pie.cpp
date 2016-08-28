#include "pie.h"

using namespace Jam;

bool Pie::_cooking = false;

Pie::Pie(Flavor& flavor)
	: _flavor(flavor)
{
	_initSDL();
	_initCores();

	SST::setEncryptionKey(flavor.sstEncryptionKey);
}

void Pie::bake()
{
	_cooking = true;

	_graphicsCore->_bake(_flavor);
	_audioCore->_bake(_flavor);

	while (!_graphicsCore->_ready || !_audioCore->_ready);

	_gameStateManager = new GameStateManager(*this, GameStateLibrary::getGameState(_flavor.enterState));

	InputHandler::_init(_flavor);

	Time::registerThread();

	while (_cooking) {
		InputHandler::_update();
		_gameStateManager->update(Time::getDelta());
		Time::wait();
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	_audioCore->join();
	_graphicsCore->join();

	Time::unregisterThread();

	InputHandler::_destroy();

	delete _gameStateManager;

	GFXLibrary::_destroy();
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
	_audioCore = new AudioCore(*this, _flavor);
}

Pie::~Pie()
{
	delete _graphicsCore;
	delete _audioCore;
	SDL_Quit();
}