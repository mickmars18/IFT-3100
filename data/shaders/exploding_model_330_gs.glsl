#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

uniform float timeSinceStart;

float getForce(float timeSinceStart) {
    return (log(timeSinceStart * 0.03 + 1.0)) * 250.0;
}

vec4 explode(vec4 position, vec3 normal)
{
    vec3 direction = normal * getForce(timeSinceStart); 
    return position + vec4(direction, 0.0);
} 

vec3 getNormal()
{
   vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
   vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
   return normalize(cross(a, b));
} 

void main() {    
    vec3 normal = getNormal();

    gl_Position = explode(gl_in[0].gl_Position, normal);
    EmitVertex();
    gl_Position = explode(gl_in[1].gl_Position, normal);
    EmitVertex();
    gl_Position = explode(gl_in[2].gl_Position, normal);
    EmitVertex();
    EndPrimitive();
} 