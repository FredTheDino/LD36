#pragma once

#include "gllibrary.h"
#include "glshaderprogram.h"
#include "glmesh.h"
#include "material.h"

namespace Jam
{
	class Renderer;
	struct Material;

	class GLRenderer
	{
	public:
		GLRenderer(Renderer& renderer, std::string mesh, std::string shaderProgram, Material& material);

		void draw();

		void setMesh(GLMesh* mesh);

		void setShaderProgram(GLShaderProgram* shaderProgram);
	
		GLMesh* getMesh() { return _mesh; };

		GLShaderProgram* getShaderProgram() { return _shaderProgram; };

		Material& getMaterial() { return _material; };

	private:
		
		Renderer& _renderer;

		GLMesh* _mesh;

		GLShaderProgram* _shaderProgram;

		Material& _material;

		friend Renderer;
	};
}