// basis of the shader from Sparky Game engine.
// https://github.com/TheCherno/Sparky

#version 330 core

in DATA {
    vec4 position;
    vec2 uv;
    float tid;
    vec4 color;
} fs_in;

uniform sampler2D textures;

void main() {
    vec4 texColor = fs_in.color;
    // int tid = int(fs_in.tid - 0.5);
    texColor = fs_in.color * texture(textures, fs_in.uv);
}
