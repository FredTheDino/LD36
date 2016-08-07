#pragma once

#include <string>

#include "renderengine.h"

#include "graphicscoretype.h"
#include "glrenderer.h"
#include "glmesh.h"
#include "gllibrary.h"

namespace Jam
{
	//Forward declaration
	class RenderEngine;
	class GLRenderer;

	class Renderer
	{
	public:
		Renderer(RenderEngine* renderEngine, std::string mesh = "quad");
		~Renderer();

		const GraphicsCoreType GRAPHICS_TYPE;

		void draw();

		void setMesh(std::string tag);

	private:

		RenderEngine* _renderEngine;

		GLRenderer* _glRenderer;


	};
}