#version 330 core

uniform mat4 projection;
uniform mat4 modelview;
uniform mat3 textureMatrix;

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 uv;

out vec2 textureCoord;
out vec3 ourcolor;

void main()
{
	gl_Position = projection * modelview * position;
	textureCoord = uv;
	ourcolor = color;
	// textureCoord = (vec3(uv, 0) * textureMatrix).xy;
}
