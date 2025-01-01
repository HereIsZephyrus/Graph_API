#version 410 core

in float transparent_y;
out vec4 color;
uniform float transparent_time;

void main() {
    float transparent = transparent_time * 2 + transparent_y;
    vec3 white = vec3(1.0f,1.0f,1.0f);
    color = vec4(white * transparent, 1.0f);
    color = clamp(color, 0.0, 1.0);
}
