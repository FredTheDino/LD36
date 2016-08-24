#pragma once

#include "lodepng/lodepng.h"
#include "GL/glew.h"

#include "texture.h"
#include "loader.h"

namespace Jam
{
	class GLTexture
	{
	public:
		GLTexture(Texture& texture);
		~GLTexture();

		void bind(unsigned int target = 0);

	private:
		
		GLuint _id;

		unsigned int _width;
		unsigned int _height;

		void _generate(Texture& texture);

		GLenum _evaluateTexParam(TextureParam texParam);

	};
}