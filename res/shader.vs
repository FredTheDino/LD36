#version 330

in vec3 position;


out vec2 texCoord;

uniform vec2 spriteDimensions;
uniform int subSprite;
uniform mat4 translationMatrix;
uniform sampler2D texture;

void main()
{
	gl_Position = translationMatrix * vec4(position * 1, 1.0);

	texCoord = vec2(position.x + 0.5, position.y + 0.5);

	//Flip the texture vertically
	texCoord.y = 1 - texCoord.y;

	texCoord.x *= spriteDimensions.x;
	texCoord.y *= spriteDimensions.y;

	float numSprites = (1.0 / spriteDimensions.x);
	float x = mod(subSprite, numSprites);
	float y = ((subSprite - x) / (1 / spriteDimensions.x));

	texCoord.x += spriteDimensions.x * x;
	texCoord.y += spriteDimensions.y * y;

	//texCoord.x = 1 - texCoord.x;
}
