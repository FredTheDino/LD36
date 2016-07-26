#version 330

out vec4 color;

in vec2 texCoord;

uniform sampler2D texture;

void main()
{
	color = texture2D(texture, texCoord);//vec4(0.5, 0, 0.5, 1.0);
}
