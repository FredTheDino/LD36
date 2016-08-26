#version 410

uniform mat4 model;

layout(location=0) in vec2 in_pos;
layout(location=1) in vec2 in_texCoords;

out vec2 pass_texCoords;

void main()
{
	
	pass_texCoords = in_texCoords;

	//The W compoonent also got scaled, counteract this by subtracting 1 from it
	gl_Position = (model * vec4(in_pos, 0, 1)) * 2.0 - vec4(1.0, 1.0, 0.0, 1.0);
	//pass_texCoords = pos * 10;
	//gl_Position = vec4(in_pos, 0, 1);
}