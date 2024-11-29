#version 330

out vec4 out_color;
in vec2 v_texture_coords;

uniform sampler2D image_texture;

void main() {
    vec4 tex_color = texture(image_texture, v_texture_coords);
    float y = (tex_color.x + tex_color.y + tex_color.z) / 3.0f;

    out_color = vec4(y, y, y, tex_color.w);
}
