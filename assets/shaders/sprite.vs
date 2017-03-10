// basis of the shader from Sparky Game engine.
// https://github.com/TheCherno/Sparky


#version 330 core
layout (location = 0) in vec4 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in float tid;
layout (location = 3) in vec4 color;

uniform mat4 projection;

out DATA {
    vec4 position;
    vec2 uv;
    float tid;
    vec4 color;
} fs_out;

void main() {
    gl_Position = projection * position;
    fs_out.position = position;
    fs_out.uv = uv;
    fs_out.tid = tid;
    fs_out.color = color;
}