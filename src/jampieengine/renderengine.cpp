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

	_loadDefaultContent();
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
			case LOAD_TYPE_MESH: le.load ? GLLibrary::_loadMesh(le.tag) : GLLibrary::_unloadMesh(le.tag); break;
			case LOAD_TYPE_SHADER_PROGRAM: le.load ? GLLibrary::_loadShaderProgram(le.tag) : GLLibrary::_unloadShaderProgram(le.tag); break;
			case LOAD_TYPE_TEXTURE: le.load ? GLLibrary::_loadTexture(le.tag) : GLLibrary::_unloadTexture(le.tag); break;
			case LOAD_TYPE_SPRITE_SHEET: le.load ? GLLibrary::_loadSpriteSheet(le.tag) : GLLibrary::_unloadSpriteSheet(le.tag); break;
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

		if (_cancelRendering) {
			_cancelRendering = false;
			break;
		}
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
		glClearColor(_graphicsCore._pie._flavor.bgColorR, _graphicsCore._pie._flavor.bgColorG,
			_graphicsCore._pie._flavor.bgColorB, _graphicsCore._pie._flavor.bgColorA);
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

void RenderEngine::_loadDefaultContent()
{
	/* Quad mesh initialization */
	Mesh mesh{};

	//Quad vertices
	std::vector<Vertex*> quad;
	
	quad.push_back((Vertex*) new Vertex2D(-.5f, .5f, 0, 0));
	quad.push_back((Vertex*) new Vertex2D(.5f, .5f, 1, 0));
	quad.push_back((Vertex*) new Vertex2D(.5f, -.5f, 1, 1));
	quad.push_back((Vertex*) new Vertex2D(-.5f, -.5f, 0, 1));

	mesh.vertices = quad;

	//Quad indices

	unsigned int indices[6] = { 0, 1, 3, 3, 1, 2 };

	mesh.indices = indices;
	mesh.indexCount = 6;

	mesh.shaderProgram = "ortho";

	//Register quad
	GFXLibrary::registerMesh("quad", mesh);

	//Preload mesh for GPU loading
	preloadMesh("quad");

	/* Ortho shader program initialization */
	ShaderProgram shaderProgram;

	//Loads shader program
	shaderProgram.vertexShader = Loader::loadText("shader/2D.vsh");
	shaderProgram.fragmentShader = Loader::loadText("shader/2D.fsh");


	//Register shader program
	GFXLibrary::registerShaderProgram("ortho", shaderProgram);


	//Preload shader program for GPU loading
	preloadShaderProgram("ortho");

	/* GUI shader program initialization */

	Jam::ShaderProgram guiShaderProgram;

	guiShaderProgram.vertexShader = Jam::Loader::loadText("shader/GUIShader.vert");
	guiShaderProgram.fragmentShader = Jam::Loader::loadText("shader/GUIShader.frag");

	Jam::GFXLibrary::registerShaderProgram("GUIShader", guiShaderProgram);

	Jam::RenderEngine::preloadShaderProgram("GUIShader");

	/* Default texture initialization */
	Texture texture;

	//Texture size 1x1
	texture.width = 1;
	texture.height = 1;

	//Completely white
	std::vector<unsigned char> data(4);
	data[0] = UCHAR_MAX;
	data[1] = UCHAR_MAX;
	data[2] = UCHAR_MAX;
	data[3] = UCHAR_MAX;

	texture.data = data;

	//Register texture
	GFXLibrary::registerTexture("default", texture);

	//Preload texture for GPU loading
	preloadTexture("default");

	/* Load to GPU */
	_load();
}

RenderEngine::~RenderEngine()
{
	_deleteContext();
}