#version 430 core

out vec4 color;

in vec2 uv0;

uniform sampler2D mytexture;

void main()
{
	color = texture2D(mytexture,uv0);
	//color = vec4(1.0, 0.0, 0.0, 1.0);
}