#pragma once

#include <unordered_map>

#include "mesh.h"
#include "shaderprogram.h"

namespace Jam
{
	class GFXLibrary
	{
	public:

		//User mesh interaction
		static void registerMesh(std::string tag, Mesh mesh) { _meshRegistry.insert(std::make_pair(tag, mesh)); };
		static Mesh getMesh(std::string tag) { return _meshRegistry.at(tag); };

		//User shader program interaction
		static void registerShaderProgram(std::string tag, ShaderProgram shaderProgram) { _shaderProgramRegistry.insert(std::make_pair(tag, shaderProgram)); };
		static ShaderProgram getShaderProgram(std::string tag) { return _shaderProgramRegistry.at(tag); };

	private:
		//Generic meshes
		static std::unordered_map<std::string, Mesh> _meshRegistry;

		//Generic shader programs
		static std::unordered_map<std::string, ShaderProgram> _shaderProgramRegistry;
	};
}