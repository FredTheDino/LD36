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
		Renderer(RenderEngine* renderEngine, int priority = 0, std::string mesh = "quad", Material material = {}, std::string shaderProgram = "");
		Renderer(RenderEngine* renderEngine, int priority = 0, std::string mesh = "quad", std::string texture = "default", std::string shaderProgram = "");
		~Renderer();

		const GraphicsCoreType GRAPHICS_TYPE;

		virtual void draw();

		void setMesh(std::string tag);
		void setShaderProgram(std::string tag);
		
		void setTexture(std::string tag);

		void setTexture(std::string spriteSheet, unsigned int x, unsigned int y);

		void _rootEnter();
		void _init();
		void _update(double delta) {};
		void _end() {};
		void _rootExit();

		void setShouldDraw(bool shouldDraw) { _shouldDraw = shouldDraw; };
		bool shouldDraw() { return _shouldDraw; };

	protected:

		unsigned int _associationID;

		int _priority;

		bool _shouldDraw = false;

		Material _material;

		std::string _mesh;

		std::string _shaderProgram;

		RenderEngine* _renderEngine;

		GLRenderer* _glRenderer;

		friend GLRenderer;
	};
}