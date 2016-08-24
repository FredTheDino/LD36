#pragma once

#include <vector>

namespace Jam
{
	enum TextureParam {
		TEX_PARAM_NEAREST,
		TEX_PARAM_LINEAR,
		TEX_PARAM_CLAMP,
		TEX_PARAM_REPEAT
	};

	struct Texture {
		std::string path;
		std::vector<unsigned char> data;
		unsigned int width;
		unsigned int height;
		TextureParam minFilter = TEX_PARAM_NEAREST;
		TextureParam magFilter = TEX_PARAM_NEAREST;
		TextureParam wrapS = TEX_PARAM_REPEAT;
		TextureParam wrapT = TEX_PARAM_REPEAT;
	};
}