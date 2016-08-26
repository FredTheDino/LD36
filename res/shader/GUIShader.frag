#version 410

uniform vec4 color = vec4(1, 1, 1, 1);
uniform sampler2D texture;

//If it is using all the other data
uniform bool isFader;
//A slider between 0 and 1
uniform float value;
//The texture that represents values that are less than "value" uses to draw
uniform sampler2D textureOff;
//A map that gives each pixel a value
uniform sampler2D valueTexture;

layout(location=0) out vec4 out_color;

in vec2 pass_texCoords;

void main()
{
	if (isFader) {
		//Use the fader variables
		if (value <= texture2D(valueTexture, pass_texCoords).x) {
			out_color = texture2D(texture, pass_texCoords) * color;
			return;
		} else {
			out_color = texture2D(textureOff, pass_texCoords) * color;
			return;
		}
	} else {
		//Don't use the special case
		out_color = texture2D(texture, pass_texCoords) * color;
		return;
	}
}