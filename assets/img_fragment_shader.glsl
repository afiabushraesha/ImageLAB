#version 330

out vec4 out_color;
in vec2 v_texture_coords;

uniform sampler2D image_texture;

void main() {
    out_color = texture(image_texture, v_texture_coords);
}
