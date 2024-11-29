#version 330

layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 texture_coords;

uniform mat4 proj;
uniform mat4 view;
out vec2 v_texture_coords;

void main() {
    gl_Position = proj * view * vec4(pos, 0.0f, 1.0f);
    v_texture_coords = texture_coords;
}
