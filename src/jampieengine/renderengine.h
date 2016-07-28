#pragma once

#include "SDL2/SDL.h"
#include "GLEW/glew.h"

#include "graphicscore.h"
#include "window.h"

namespace Jam
{
	//Forward declaration
	class GraphicsCore;


	class RenderEngine
	{
	public:
		RenderEngine(Window& window, GraphicsCoreType graphicsType);
		~RenderEngine();

	private:

		GraphicsCoreType _graphicsType;

		Window& _window;

		SDL_GLContext _glContext;

		//Called each frame
		void _draw();

		//Creates context of selected graphics API
		void _createContext();

		//Deletes context of selected graphics API
		void _deleteContext();

		//Friends!
		friend GraphicsCore;
	};
}