#version 330 core

uniform mat4 projection;
uniform mat4 modelview;

layout (location = 0) in vec4 vertex;

out vec2 textureCoord;

void main()
{
	textureCoord = vertex.zw;
  gl_Position = projection * modelview * vec4(vertex.xy, 0.0, 1.0);
}
