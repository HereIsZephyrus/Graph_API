#version 410 core

layout(lines) in;
layout(triangle_strip, max_vertices = 15) out;
in vec3 geoColor[];
out vec3 fragColor;

void main() {
    fragColor = geoColor[0];
    vec4 p0 =  gl_in[0].gl_Position;
    vec4 p1 =  gl_in[1].gl_Position;
    vec2 direction = normalize(p1.xy - p0.xy) / 10;
    float width =  distance(p0,p1)/5;
    vec2 normal = vec2(-direction.y, direction.x) * width ;
    float arrowWidthRate =  4;
    vec4 noHaedp1 = p1 - vec4(direction * width * arrowWidthRate / 2,0.0,0.0);

    gl_Position = p0 + vec4(-normal.x, -normal.y, 0.0, 0.0);
    EmitVertex();
    gl_Position = p0 + vec4(normal.x, -normal.y, 0.0, 0.0);
    EmitVertex();
    gl_Position = p0 + vec4(-normal.x, normal.y,0.0, 0.0);
    EmitVertex();
    gl_Position = p0 + vec4(normal.x, normal.y , 0.0, 0.0);
    EmitVertex();
    
    gl_Position = p0 - vec4(normal, 0.0, 0.0);
    EmitVertex();
    gl_Position = noHaedp1 + vec4(normal, 0.0, 0.0);
    EmitVertex();
    
    gl_Position = noHaedp1 + vec4(-normal.x, -normal.y, 0.0, 0.0);
    EmitVertex();
    gl_Position = noHaedp1 + vec4(-normal.x, normal.y, 0.0, 0.0);
    EmitVertex();
    gl_Position = noHaedp1 + vec4(normal.x, -normal.y, 0.0, 0.0);
    EmitVertex();
    gl_Position = noHaedp1 + vec4(normal.x, normal.y , 0.0, 0.0);
    EmitVertex();
    // arrow
    gl_Position = noHaedp1 + vec4(normal, 0.0, 0.0) * arrowWidthRate;
    EmitVertex();
    gl_Position = noHaedp1 - vec4(normal, 0.0, 0.0) * arrowWidthRate;
    EmitVertex();
    gl_Position = p1;
    EmitVertex();
    EndPrimitive();
}
