#pragma once

#include <unordered_map>

#include "mesh.h"
#include "shaderprogram.h"
#include "texture.h"
#include "spritesheet.h"

namespace Jam
{
	class Pie;

	class GFXLibrary
	{
	public:

		//User mesh interaction
		static void registerMesh(std::string tag, Mesh mesh) { _meshRegistry.insert(std::make_pair(tag, mesh)); };
		static void removeMesh(std::string tag) { _meshRegistry.erase(tag); };
		static Mesh getMesh(std::string tag) { return _meshRegistry.at(tag); };

		//User shader program interaction
		static void registerShaderProgram(std::string tag, ShaderProgram shaderProgram) { _shaderProgramRegistry.insert(std::make_pair(tag, shaderProgram)); };
		static ShaderProgram getShaderProgram(std::string tag) { return _shaderProgramRegistry.at(tag); };

		//User texture interaction
		static void registerTexture(std::string tag, Texture texture) { _textureRegistry.insert(std::make_pair(tag, texture)); };
		static Texture getTexture(std::string tag) { return _textureRegistry.at(tag); };

		//User sprite sheet interaction
		static void registerSpriteSheet(std::string tag, SpriteSheet spriteSheet) { _spriteSheetRegistry.insert(std::make_pair(tag, spriteSheet)); };
		static SpriteSheet getSpriteSheet(std::string tag) { return _spriteSheetRegistry.at(tag); };

	private:
		//Generic meshes
		static std::unordered_map<std::string, Mesh> _meshRegistry;

		//Generic shader programs
		static std::unordered_map<std::string, ShaderProgram> _shaderProgramRegistry;

		//Generic textures
		static std::unordered_map<std::string, Texture> _textureRegistry;

		//Generic sprite sheet
		static std::unordered_map<std::string, SpriteSheet> _spriteSheetRegistry;

		static void _destroy();

		friend Pie;
	};
}