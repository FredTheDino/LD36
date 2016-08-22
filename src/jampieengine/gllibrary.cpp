#include "gllibrary.h"

using namespace Jam;

RenderEngine* GLLibrary::_renderEngine;

std::unordered_map<std::string, GLMesh*> GLLibrary::_glMeshRegistry;
std::unordered_map<std::string, GLShaderProgram*> GLLibrary::_glShaderProgramRegistry;
std::unordered_map<std::string, GLTexture*> GLLibrary::_glTextureRegistry;

void GLLibrary::_unloadAll()
{

	//Unload mesh map
	for (std::unordered_map<std::string, GLMesh*>::iterator it = _glMeshRegistry.begin(); it != _glMeshRegistry.end(); ++it) {
		delete it->second;
	}

	//Clear mesh map
	_glMeshRegistry.clear();

	//Unload shader program map
	for (std::unordered_map<std::string, GLShaderProgram*>::iterator it = _glShaderProgramRegistry.begin(); it != _glShaderProgramRegistry.end(); ++it) {
		delete it->second;
	}

	//Clear shader program map
	_glShaderProgramRegistry.clear();

	//Unload texture map
	for (std::unordered_map<std::string, GLTexture*>::iterator it = _glTextureRegistry.begin(); it != _glTextureRegistry.end(); ++it) {
		delete it->second;
	}

	//Clear texture map
	_glTextureRegistry.clear();
}