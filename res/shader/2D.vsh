#version 410

uniform mat4 transform;

layout(location=0) in vec2 in_pos;

void main()
{
	gl_Position = transform * vec4(in_pos, 0, 1);
}