#pragma once

#include "graphicscoretype.h"
#include "glrenderer.h"

namespace Jam
{
	class Renderer
	{
	public:
		Renderer(GraphicsCoreType graphicsType);
		~Renderer();

		const GraphicsCoreType GRAPHICS_TYPE;

	private:

		GLRenderer* _glRenderer;


	};
}