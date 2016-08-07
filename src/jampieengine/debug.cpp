#include "debug.h"

void Jam::Debug::err(std::string msg, int err)
{
#ifdef _DEBUG
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "The pie was burnt!", msg.c_str(), NULL);
#else
	std::cout << msg << std::endl;
#endif

	std::exit(err);
}