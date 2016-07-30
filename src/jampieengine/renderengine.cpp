#include "renderengine.h"

using namespace Jam;

RenderEngine::RenderEngine(Window& window, GraphicsCoreType graphicsType)
	: _window(window), _graphicsType(graphicsType)
{
	_createContext();
}

void RenderEngine::_draw()
{
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	SDL_GL_SwapWindow(_window.getHandle());
}

void RenderEngine::_createContext()
{
	switch (_graphicsType) {
	case GRAPHICS_TYPE_OPENGL:
		_glContext = SDL_GL_CreateContext(_window.getHandle());
		SDL_GL_SetSwapInterval(0);
		break;
	}
}

void RenderEngine::_deleteContext()
{
	switch (_graphicsType) {
	case GRAPHICS_TYPE_OPENGL:
		SDL_GL_DeleteContext(_glContext);
		break;
	}
}

RenderEngine::~RenderEngine()
{
	_deleteContext();
}