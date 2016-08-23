#pragma once

#include <unordered_map>

#include "renderengine.h"
#include "glmesh.h"
#include "glshaderprogram.h"
#include "gfxlibrary.h"

namespace Jam
{
	//Forward declaration
	class RenderEngine;

	class GLLibrary
	{
	public:

		//Return loaded mesh
		static GLMesh* getMesh(std::string tag) { return _glMeshRegistry.at(tag); };

		//Return loaded shader program
		static GLShaderProgram* getShaderProgram(std::string tag) { return _glShaderProgramRegistry.at(tag); };

	private:

		//Render engine
		static RenderEngine* _renderEngine;

		//Loaded meshes
		static std::unordered_map<std::string, GLMesh*> _glMeshRegistry;

		//Instantiate GLMesh from generic mesh associated with tag (has to be called from graphicscore thread)
		static void _loadMesh(std::string tag) {
			Mesh mesh = GFXLibrary::getMesh(tag);
			GLMesh* glmesh = new GLMesh(mesh);
			_glMeshRegistry.insert(std::make_pair(tag, glmesh)); 
		};

		//Unloads GLMesh with specified tag (has to be called from graphicscore thread)
		static void _unloadMesh(std::string tag) { delete _glMeshRegistry.at(tag); _glMeshRegistry.erase(tag); };

		//Loaded shader programs
		static std::unordered_map<std::string, GLShaderProgram*> _glShaderProgramRegistry;

		//Instantiate GLShaderProgram from generic shader program associated with tag (has to be called from graphicscore thread)
		static void _loadShaderProgram(std::string tag) {
			ShaderProgram program = GFXLibrary::getShaderProgram(tag);
			_glShaderProgramRegistry.insert(std::make_pair(tag, new GLShaderProgram(program))); 
		};

		//Unloads GLShaderProgram with specified tag (has to be called from graphicscore thread)
		static void _unloadShaderProgram(std::string tag) { delete _glShaderProgramRegistry.at(tag); _glShaderProgramRegistry.erase(tag); };

		//Unloads everything from this library
		static void _unloadAll();

		friend RenderEngine;
	};
}