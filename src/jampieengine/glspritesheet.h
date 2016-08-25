#pragma once

#include "lodepng/lodepng.h"

#include "spritesheet.h"
#include "gltexture.h"
#include "loader.h"

namespace Jam
{
	class GLSpriteSheet
	{
	public:
		GLSpriteSheet(SpriteSheet& spriteSheet);

		GLTexture* getTexture(unsigned int x, unsigned int y) { return _textures[y][x]; };

	private:

		std::vector<std::vector<GLTexture*>> _textures;

		void _generate(SpriteSheet& spriteSheet);
	};
}