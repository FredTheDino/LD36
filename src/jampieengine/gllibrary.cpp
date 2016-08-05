#include "gllibrary.h"

using namespace Jam;

RenderEngine* GLLibrary::_renderEngine;

std::unordered_map<std::string, GLMesh*> GLLibrary::_glMeshRegistry;
std::unordered_map<std::string, GLShaderProgram*> GLLibrary::_glShaderProgramRegistry;

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
	_glMeshRegistry.clear();
}