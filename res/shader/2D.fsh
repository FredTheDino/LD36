#version 410

layout(location=0) out vec4 out_color;

void main()
{
	out_color = vec4(gl_FragCoord.x / 800, gl_FragCoord.y / 300, (gl_FragCoord.x / 800) * (gl_FragCoord.y / 300), 1);
}