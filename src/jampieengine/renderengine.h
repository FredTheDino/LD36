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
#include "camera.h"

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
		RenderEngine(GraphicsCore& graphicsCore, Window& window, GraphicsCoreType graphicsType, Camera* camera);
		~RenderEngine();

		//Adds mesh associated with tag to load queue
		static void preloadMesh(std::string tag) { while (_accessingLoadQueues); _loadQueue.push_back(LoadEntry{ LOAD_TYPE_MESH, tag }); };

		//Adds shader program associated with tag to load queue
		static void preloadShaderProgram(std::string tag) { while (_accessingLoadQueues); _loadQueue.push_back(LoadEntry{ LOAD_TYPE_SHADER_PROGRAM, tag }); };

		//Adds texture associated with tag to load queue
		static void preloadTexture(std::string tag) { while (_accessingLoadQueues); _loadQueue.push_back(LoadEntry{ LOAD_TYPE_TEXTURE, tag }); };

		//Sets _shouldLoad to true in order to process load queue on render thread
		static void load() { _accessingLoadQueues = true; _shouldLoad = true; };

		//Adds something to draw, returns an association ID
		unsigned int addRenderer(int priority, Renderer* renderer);

		//Removes the renderer with the specified association id
		void removeRenderer(unsigned int associationID);

		//Returns the camera currently used by this render engine
		Camera* getCamera() { return _camera; };

		//Sets the camera to be used by this render engine
		void useCamera(Camera* camera) { _camera = camera; };

		Window& getWindow() { return _window; }

		//Returns the number of remaining load entries
		static unsigned int remainingLoadEntries() { return _loadQueue.size(); };

		const GraphicsCoreType GRAPHICS_TYPE;

	private:

		unsigned int _rendererIDCounter = 0;

		enum LoadType {
			LOAD_TYPE_MESH,
			LOAD_TYPE_SHADER_PROGRAM,
			LOAD_TYPE_TEXTURE
		};

		struct LoadEntry {
			LoadType loadType;
			std::string tag;
		};

		Camera* _camera;

		GraphicsCore& _graphicsCore;

		Window& _window;

		SDL_GLContext _glContext;

		//Booleans used to communicate between threads
		static bool _shouldLoad;
		static bool _accessingLoadQueues;

		//Queue of load entries
		static std::vector<LoadEntry> _loadQueue;

		//Objects to render each frame
		std::multimap<int, std::pair<unsigned int, Renderer*>, std::less<int>> _renderers;

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