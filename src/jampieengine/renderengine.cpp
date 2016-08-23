#include "renderengine.h"

using namespace Jam;

//Static instantiation
bool RenderEngine::_shouldLoad;
bool RenderEngine::_accessingLoadQueues;
std::vector<RenderEngine::LoadEntry> RenderEngine::_loadQueue;

RenderEngine::RenderEngine(GraphicsCore& graphicsCore, Window& window, GraphicsCoreType graphicsType, Camera* camera)
	: _graphicsCore(graphicsCore), _window(window), GRAPHICS_TYPE(graphicsType), _camera(camera)
{
	_createContext();
	

	std::cout << "TODO: Remove default quad mesh from renderengine.cpp constructor" << std::endl;
	/* Quad Start */
	Mesh mesh{};

	std::vector<Vertex*> quad;
	quad.push_back((Vertex*) new Vertex2D(-.5f, .5f, 0, 0));
	quad.push_back((Vertex*) new Vertex2D(.5f, .5f, 1, 0));
	quad.push_back((Vertex*) new Vertex2D(.5f, -.5f, 1, 1));
	quad.push_back((Vertex*) new Vertex2D(-.5f, -.5f, 0, 1));

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

	std::cout << "TODO: Remove default texture from renderengine.cpp constructor" << std::endl;
	/* Texture Start */

	Texture texture;
	texture.width = 1;
	texture.height = 1;

	std::vector<unsigned char> data(4);
	data[0] = UCHAR_MAX;
	data[1] = UCHAR_MAX;
	data[2] = UCHAR_MAX;
	data[3] = UCHAR_MAX;

	texture.data = data;
	
	GFXLibrary::registerTexture("default", texture);

	preloadTexture("default");

	/* Texture End */

	/* Load to GPU */
	_load();
}

unsigned int RenderEngine::addRenderer(int priority, Renderer* renderer)
{
	_rendererIDCounter++;

	_renderers.insert(std::make_pair(priority, std::make_pair(_rendererIDCounter, renderer)));

	return _rendererIDCounter;
}

void RenderEngine::removeRenderer(unsigned int associationID)
{
	for (std::multimap<int, std::pair<unsigned int, Renderer*>>::iterator it = _renderers.begin(); it != _renderers.end();) {
		std::multimap<int, std::pair<unsigned int, Renderer*>>::iterator it_erase = it++;

		if (it_erase->second.first == associationID) {
			_renderers.erase(it_erase);
			break;
		}
	}
}

void RenderEngine::_load()
{
	switch (GRAPHICS_TYPE) {
	case GRAPHICS_TYPE_OPENGL:
		
		//Iterates load queue
		while (_loadQueue.size() > 0) {
			LoadEntry le = _loadQueue.back();

			switch (le.loadType) {
			case LOAD_TYPE_MESH: GLLibrary::_loadMesh(le.tag); break;
			case LOAD_TYPE_SHADER_PROGRAM: GLLibrary::_loadShaderProgram(le.tag); break;
			case LOAD_TYPE_TEXTURE: GLLibrary::_loadTexture(le.tag); break;
			}

			_loadQueue.pop_back();
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

	for (const std::pair<int, std::pair<unsigned int, Renderer*>> renderer : _renderers) {
		renderer.second.second->draw();
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
		glEnable(GL_TEXTURE_2D);
		if (_graphicsCore._pie._flavor.transparancy) {
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
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