#pragma once

#include "texture.h"

namespace Jam
{
	struct SpriteSheet {
		std::string path;
		std::vector<unsigned char> data;
		unsigned int width;
		unsigned int height;
		TextureParam minFilter = TEX_PARAM_NEAREST;
		TextureParam magFilter = TEX_PARAM_NEAREST;
		TextureParam wrapS = TEX_PARAM_REPEAT;
		TextureParam wrapT = TEX_PARAM_REPEAT;
		unsigned int tilesX;
		unsigned int tilesY;
	};
}