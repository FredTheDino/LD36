#include "renderer.h"

using namespace Jam;

Renderer::Renderer(GraphicsCoreType graphicsType)
	: GRAPHICS_TYPE(graphicsType)
{
	switch (graphicsType) {
	case GRAPHICS_TYPE_OPENGL:
		_glRenderer = new GLRenderer();
		break;
	}
}



Renderer::~Renderer()
{
	switch (GRAPHICS_TYPE) {
	case GRAPHICS_TYPE_OPENGL:
		delete _glRenderer;
		break;
	}
}