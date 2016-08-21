#pragma once

#include <map>

#include "SDL2/SDL.h"
#include "GL/glew.h"

#include "graphicscore.h"
#include "window.h"
#include "gllibrary.h"
#include "renderer.h"

#include "vertex2d.h"
#include "mesh.h"
#include "glmesh.h"
#include "loader.h"

namespace Jam
{
	//Forward declaration
	class GraphicsCore;
	class Window;
	class GLLibrary;
	class Renderer;

	class RenderEngine
	{
	public:
		RenderEngine(Window& window, GraphicsCoreType graphicsType);
		~RenderEngine();

		//Adds mesh associated with tag to load queue
		static void preloadMesh(std::string tag) { while (_accessingLoadQueues); _meshLoadQueue.push_back(tag); };

		//Adds shader program associated with tag to load queue
		static void preloadShaderProgram(std::string tag) { while (_accessingLoadQueues); _shaderProgramLoadQueue.push_back(tag); };
		
		//Sets _shouldLoad to true in order to process load queue on render thread
		static void load() { _accessingLoadQueues = true; _shouldLoad = true; };

		//Adds something to draw
		void addRenderer(int priority, Renderer* renderer) { _renderers.insert(std::make_pair(priority, renderer)); };

		const GraphicsCoreType GRAPHICS_TYPE;

	private:

		Window& _window;

		SDL_GLContext _glContext;

		//Booleans used to communicate between threads
		static bool _shouldLoad;
		static bool _accessingLoadQueues;

		//Queue of meshes to load
		static std::vector<std::string> _meshLoadQueue;

		//Queue of shader programs to load
		static std::vector<std::string> _shaderProgramLoadQueue;

		//Objects to render each frame
		std::multimap<int, Renderer*, std::less<int>> _renderers;

		//Processes load queue and loads everything
		void _load();

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