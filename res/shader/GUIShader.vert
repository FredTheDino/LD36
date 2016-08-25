#version 410

uniform mat4 model;
uniform vec2 offset;
//uniform vec2 screen;

layout(location=0) in vec2 in_pos;
layout(location=1) in vec2 in_texCoords;

out vec2 pass_texCoords;

void main()
{
	
	pass_texCoords = in_texCoords;

	gl_Position = model * vec4(in_pos, 0, 1);
	//pass_texCoords = pos * 10;
	//gl_Position = vec4(in_pos, 0, 1);
}