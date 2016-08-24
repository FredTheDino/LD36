#version 410

uniform vec4 color = vec4(1, 1, 1, 1);
uniform sampler2D texture;

layout(location=0) out vec4 out_color;

in vec2 pass_texCoords;

void main()
{
	out_color = texture2D(texture, pass_texCoords) * color;
}