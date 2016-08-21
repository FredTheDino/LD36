#include "renderengine.h"

using namespace Jam;

//Static instantiation
bool RenderEngine::_shouldLoad;
bool RenderEngine::_accessingLoadQueues;
std::vector<std::string> RenderEngine::_meshLoadQueue;
std::vector<std::string> RenderEngine::_shaderProgramLoadQueue;

RenderEngine::RenderEngine(Window& window, GraphicsCoreType graphicsType)
	: _window(window), GRAPHICS_TYPE(graphicsType)
{
	_createContext();
	

	std::cout << "TODO: Remove default quad mesh from renderengine.cpp constructor" << std::endl;
	/* Quad Start */
	Mesh mesh{};

	std::vector<Vertex*> quad;
	quad.push_back((Vertex*) new Vertex2D(-.5f, .5f));
	quad.push_back((Vertex*) new Vertex2D(.5f, .5f));
	quad.push_back((Vertex*) new Vertex2D(.5f, -.5f));
	quad.push_back((Vertex*) new Vertex2D(-.5f, -.5f));

	mesh.vertices = quad;

	unsigned int indices[6] = {0, 1, 3, 3, 1, 2};

	mesh.indices = indices;
	mesh.indexCount = 6;

	mesh.shaderProgram = "2D";

	//Register generic mesh
	GFXLibrary::registerMesh("quad", mesh);

	//Preload for GPU loading
	preloadMesh("quad");
	
	/* Quad End */

	std::cout << "TODO: Remove default shader program from renderengine.cpp constructor" << std::endl;
	/* Shader Program Start */

	ShaderProgram shaderProgram;

	shaderProgram.vertexShader = Loader::loadText("shader/2D.vsh");
	shaderProgram.fragmentShader = Loader::loadText("shader/2D.fsh");

	GFXLibrary::registerShaderProgram("2D", shaderProgram);

	preloadShaderProgram("2D");

	/* Shader Program End */

	/* Load to GPU */
	_load();
}

void RenderEngine::_load()
{
	switch (GRAPHICS_TYPE) {
	case GRAPHICS_TYPE_OPENGL:
		
		//Iterates mesh load queue
		while (_meshLoadQueue.size() > 0) {
			GLLibrary::_loadMesh(_meshLoadQueue.back());
			_meshLoadQueue.pop_back();
		}

		//Iterates shader program load queue
		while (_shaderProgramLoadQueue.size() > 0) {
			GLLibrary::_loadShaderProgram(_shaderProgramLoadQueue.back());
			_shaderProgramLoadQueue.pop_back();
		}

		break;
	}
}

void RenderEngine::_draw()
{
	//Should enter loading stance?
	if (_shouldLoad) {
		_shouldLoad = false;
		_load();
		_accessingLoadQueues = false;
	}

	glClear(GL_COLOR_BUFFER_BIT);

	for (const std::pair<int, Renderer*> renderer : _renderers) {
		renderer.second->draw();
	}

	SDL_GL_SwapWindow(_window.getHandle());
}

void RenderEngine::_createContext()
{
	switch (GRAPHICS_TYPE) {
	case GRAPHICS_TYPE_OPENGL:
		_glContext = SDL_GL_CreateContext(_window.getHandle());
		SDL_GL_SetSwapInterval(0);
		glewExperimental = GL_TRUE;
		glewInit();
		GLLibrary::_renderEngine = this;
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		break;
	}
}

void RenderEngine::_deleteContext()
{
	switch (GRAPHICS_TYPE) {
	case GRAPHICS_TYPE_OPENGL:
		GLLibrary::_unloadAll();
		SDL_GL_DeleteContext(_glContext);
		break;
	}
}

RenderEngine::~RenderEngine()
{
	_deleteContext();
}