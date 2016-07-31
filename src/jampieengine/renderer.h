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

		void draw();

	private:

		GLRenderer* _glRenderer;


	};
}