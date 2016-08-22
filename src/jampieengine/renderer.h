#pragma once

#include <string>

#include "renderengine.h"

#include "graphicscoretype.h"
#include "glrenderer.h"
#include "glmesh.h"
#include "gllibrary.h"
#include "component.h"
#include "material.h"

namespace Jam
{
	//Forward declaration
	class RenderEngine;
	class GLRenderer;
	class Component;

	class Renderer : public Component
	{
	public:
		Renderer(RenderEngine* renderEngine, std::string mesh = "quad", Material material = {});
		~Renderer();

		const GraphicsCoreType GRAPHICS_TYPE;

		void draw();

		void setMesh(std::string tag);

		void _rootEnter();
		void _init();
		void _update(double delta) {};
		void _end() {};
		void _rootExit();

		void setShouldDraw(bool shouldDraw) { _shouldDraw = shouldDraw; };
		bool shouldDraw() { return _shouldDraw; };

	private:

		unsigned int _associationID;

		bool _shouldDraw = false;

		Material _material;

		std::string _mesh;

		RenderEngine* _renderEngine;

		GLRenderer* _glRenderer;

		friend GLRenderer;
	};
}