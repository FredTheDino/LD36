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
}

void Pie::_initSDL()
{
	int error = SDL_Init(SDL_INIT_VIDEO);

	if (error < 0) {
		Debug::err(SDL_GetError(), error);
	}
}

void Pie::_initCores()
{
	_graphicsCore = new GraphicsCore(*this, _flavor);
}

Pie::~Pie()
{
	delete _graphicsCore;

	SDL_Quit();
}