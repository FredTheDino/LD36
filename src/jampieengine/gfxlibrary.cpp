#include "gfxlibrary.h"

using namespace Jam;

std::unordered_map<std::string, Mesh> GFXLibrary::_meshRegistry;
std::unordered_map<std::string, ShaderProgram> GFXLibrary::_shaderProgramRegistry;
std::unordered_map<std::string, Texture> GFXLibrary::_textureRegistry;
std::unordered_map<std::string, SpriteSheet> GFXLibrary::_spriteSheetRegistry;

void GFXLibrary::_destroy()
{
	_meshRegistry.clear();
	_shaderProgramRegistry.clear();
	_textureRegistry.clear();
	_spriteSheetRegistry.clear();
}