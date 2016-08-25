#pragma once

#include <unordered_map>

#include "renderengine.h"
#include "glmesh.h"
#include "glshaderprogram.h"
#include "gfxlibrary.h"
#include "gltexture.h"
#include "glspritesheet.h"

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

		//Return loaded texture
		static GLTexture* getTexture(std::string tag) { return _glTextureRegistry.at(tag); };

		//Return loaded sprite sheet
		static GLSpriteSheet* getSpriteSheet(std::string tag) { return _glSpriteSheetRegistry.at(tag); };

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

		//Loaded textures
		static std::unordered_map<std::string, GLTexture*> _glTextureRegistry;

		//Instantiates GLTexture from generic texture associated with tag (has to be called from graphicscore thread)
		static void _loadTexture(std::string tag) { _glTextureRegistry.insert(std::make_pair(tag, new GLTexture(GFXLibrary::getTexture(tag)))); };

		//Unloads GLTexture with specified tag (has to be called from graphicscore thread)
		static void _unloadTexture(std::string tag) { delete _glTextureRegistry.at(tag); _glTextureRegistry.erase(tag); };

		//Loaded sprite sheets
		static std::unordered_map<std::string, GLSpriteSheet*> _glSpriteSheetRegistry;

		//Instantiates GLSpriteSheet from generic sprite sheet associated with tag (has to be called from graphicscore thread)
		static void _loadSpriteSheet(std::string tag) { _glSpriteSheetRegistry.insert(std::make_pair(tag, new GLSpriteSheet(GFXLibrary::getSpriteSheet(tag)))); };

		//Unloads GLSpriteSheet with specified tag (has to be calld from graphicscore thread)
		static void _unloadSpriteSheet(std::string tag) { delete _glSpriteSheetRegistry.at(tag); _glSpriteSheetRegistry.erase(tag); };

		//Unloads everything from this library
		static void _unloadAll();

		friend RenderEngine;
	};
}