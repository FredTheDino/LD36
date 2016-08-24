#version 410

uniform mat4 model;
uniform vec2 screen;
uniform vec2 anchor;

layout(location=0) in vec2 in_pos;
layout(location=1) in vec2 in_texCoords;

out vec2 pass_texCoords;

void main()
{
	pass_texCoords = in_texCoords;
	
	//Convert the pixel offset to actual screen space
	vec2 pos;
	pos.x = (in_pos.x / screen.x) + 1;
	pos.y = (in_pos.y / screen.y) + 1;

	pos *= 0.5;

	//gl_Position = model * vec4(pos, 0, 1) + vec4(anchor, 0, 0);
	gl_Position = vec4(in_pos, 0, 1);
}