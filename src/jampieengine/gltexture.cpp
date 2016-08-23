#include "gltexture.h"

using namespace Jam;

GLTexture::GLTexture(Texture& texture)
{
	if (texture.data.size() == 0) {
		unsigned int error = lodepng::decode(texture.data, _width, _height, Loader::prefix + texture.path);

		texture.width = _width;
		texture.height = _height;

		if (error != 0) {
			std::cout << "error " << error << ": " << lodepng_error_text(error) << std::endl;
		}
	}

	_generate(texture);
}

void GLTexture::bind(unsigned int target)
{
	glActiveTexture(GL_TEXTURE0 + target);
	glBindTexture(GL_TEXTURE_2D, _id);
}

void GLTexture::_generate(Texture& texture)
{
	glGenTextures(1, &_id);

	bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture.minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture.magFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture.wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture.wrapT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.data.data());
}

GLTexture::~GLTexture()
{
	glDeleteTextures(1, &_id);
}