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
		static void preloadMesh(std::string tag) { while (_accessingLoadQueues); _loadQueue.push_back(LoadEntry{ LOAD_TYPE_MESH, tag, true }); };

		//Adds shader program associated with tag to load queue
		static void preloadShaderProgram(std::string tag) { while (_accessingLoadQueues); _loadQueue.push_back(LoadEntry{ LOAD_TYPE_SHADER_PROGRAM, tag, true }); };

		//Adds texture associated with tag to load queue
		static void preloadTexture(std::string tag) { while (_accessingLoadQueues); _loadQueue.push_back(LoadEntry{ LOAD_TYPE_TEXTURE, tag, true }); };

		//Adds sprite sheet associated with tag to load queue
		static void preloadSpriteSheet(std::string tag) { while (_accessingLoadQueues); _loadQueue.push_back(LoadEntry{ LOAD_TYPE_SPRITE_SHEET, tag, true }); };

		//Adds mesh with associated tag to unload queue
		static void unloadMesh(std::string tag) { while (_accessingLoadQueues); _loadQueue.push_back(LoadEntry{ LOAD_TYPE_MESH, tag, false }); };

		//Adds shader program with associated tag to unload queue
		static void unloadShaderProgram(std::string tag) { while (_accessingLoadQueues); _loadQueue.push_back(LoadEntry{ LOAD_TYPE_SHADER_PROGRAM, tag, false }); };

		//Adds texture with associated tag to unload queue
		static void unloadTexture(std::string tag) { while (_accessingLoadQueues); _loadQueue.push_back(LoadEntry{ LOAD_TYPE_TEXTURE, tag, false }); };

		//Adds sprite sheet with associated tag to unload queue
		static void unloadSpriteSheet(std::string tag) { while (_accessingLoadQueues); _loadQueue.push_back(LoadEntry{ LOAD_TYPE_SPRITE_SHEET, tag, false }); };

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

		//If called by any thread, the render loop will break
		void cancelRendering() { _cancelRendering = true; };

		const GraphicsCoreType GRAPHICS_TYPE;

	private:

		unsigned int _rendererIDCounter = 0;

		enum LoadType {
			LOAD_TYPE_MESH,
			LOAD_TYPE_SHADER_PROGRAM,
			LOAD_TYPE_TEXTURE,
			LOAD_TYPE_SPRITE_SHEET
		};

		struct LoadEntry {
			LoadType loadType;
			std::string tag;
			bool load;
		};

		Camera* _camera;

		GraphicsCore& _graphicsCore;

		Window& _window;

		SDL_GLContext _glContext;

		//If set to true by any thread, the render loop will break
		bool _cancelRendering = false;

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

		//Load default content
		void _loadDefaultContent();

		//Friends!
		friend GraphicsCore;
	};
}