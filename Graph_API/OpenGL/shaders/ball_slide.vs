#version 410 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vcolor;

out float transparent_vs;

void main() {
    gl_Position = vec4(position, 1.0);
    transparent_vs = (position.y - 1)/2;
}
