#version 330 core
uniform sampler2D textures;
uniform vec3 color;

in vec2 textureCoord;
// in vec3 ourcolor;

out vec4 fragColor;
void main()
{
	fragColor = vec4(color, 0.0) * texture(textures, textureCoord);
}