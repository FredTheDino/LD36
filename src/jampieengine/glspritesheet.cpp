#include "glspritesheet.h"

using namespace Jam;

GLSpriteSheet::GLSpriteSheet(SpriteSheet spriteSheet)
{
	if (spriteSheet.data.size() == 0) {
		unsigned int error = lodepng::decode(spriteSheet.data, spriteSheet.width, spriteSheet.height, Loader::prefix + spriteSheet.path);

		if (error != 0) {
			std::cout << "error " << error << ": " << lodepng_error_text(error) << std::endl;
		}
	}

	_generate(spriteSheet);
}

void GLSpriteSheet::_generate(SpriteSheet& spriteSheet)
{
	unsigned int tileWidth = spriteSheet.width / spriteSheet.tilesX;
	unsigned int tileHeight = spriteSheet.height / spriteSheet.tilesY;

	std::cout << spriteSheet.data.size() << std::endl;

	_textures.resize(spriteSheet.tilesY);

	for (unsigned int i = 0; i < spriteSheet.tilesY; i++) {
		_textures[i] = std::vector<GLTexture*>(spriteSheet.tilesX);
		for (unsigned int j = 0; j < spriteSheet.tilesX; j++) {
			
			std::vector<unsigned char> tileData(tileWidth * tileHeight * 4);

			for (unsigned int k = 0; k < tileHeight; k++) {
				for (unsigned int l = 0; l < tileWidth * 4; l++) {
					tileData[k * tileWidth * 4 + l] = spriteSheet.data[i * spriteSheet.width * tileHeight * 4 + j * tileWidth * 4 + k * spriteSheet.width * 4 + l];
				}
			}

			Texture texture;
			texture.data = tileData;
			texture.width = tileWidth;
			texture.height = tileHeight;
			texture.minFilter = spriteSheet.minFilter;
			texture.magFilter = spriteSheet.magFilter;
			texture.wrapS = spriteSheet.wrapS;
			texture.wrapT = spriteSheet.wrapT;

			_textures[i][j] = new GLTexture(texture);
		}
	}
}

GLSpriteSheet::~GLSpriteSheet()
{
	for (std::vector<GLTexture*> row : _textures) {
		for (GLTexture* texture : row) {
			delete texture;
		}
	}

	_textures.clear();
}