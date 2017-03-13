#version 330 core
uniform sampler2D textures;

in vec2 textureCoord;
in vec3 ourcolor;

out vec4 fragColor;
void main()
{
	fragColor = texture(textures, textureCoord);
}