#include "debug.h"

void Jam::Debug::err(const char* msg, int err)
{
#ifdef _DEBUG
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "The pie was burnt!", msg, NULL);
#else
	std::cout << msg << std::endl;
#endif

	std::exit(err);
}