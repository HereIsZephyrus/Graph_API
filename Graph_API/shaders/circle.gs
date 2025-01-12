#version 410 core

layout(lines) in;
layout(triangle_strip, max_vertices = 250) out;
in vec3 geoColor[];
out vec3 fragColor;
const float width = 0.005;
const float PI = 3.14159;
const int resolution = 100;
void main() {
    fragColor = geoColor[0];
    vec4 center = gl_in[0].gl_Position;
    vec4 p1 =  gl_in[1].gl_Position;
    float radius = sqrt((center.x - p1.x) * (center.x - p1.x) + (center.y - p1.y) * (center.y - p1.y));
    float dangle = - 2 * PI / resolution;
    mat2 angleMat = mat2(
                    cos(dangle), -sin(dangle),
                    sin(dangle),  cos(dangle));
    vec2 offset = vec2(1.0,0.0);
    for (int i = 0; i <= resolution; i++){
        gl_Position = center + vec4(offset * (radius - width), 0.0, 0.0);
        EmitVertex();
        gl_Position = center + vec4(offset * (radius + width), 0.0, 0.0);
        EmitVertex();
        offset = angleMat * offset;
    }
    EndPrimitive();
}
