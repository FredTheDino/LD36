#pragma once

#include <vector>

#include "GL/glew.h"

namespace Jam
{
	struct Texture {
		std::string path;
		std::vector<unsigned char> data;
		unsigned int width;
		unsigned int height;
		GLenum minFilter = GL_NEAREST;
		GLenum magFilter = GL_NEAREST;
		GLenum wrapS = GL_REPEAT;
		GLenum wrapT = GL_REPEAT;
	};
}