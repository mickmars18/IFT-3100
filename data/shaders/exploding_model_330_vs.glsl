#version 330

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

in vec4 position;
in vec3 normal;

out VS_OUT {
    vec3 normal;
} vs_out;

void main()
{
    gl_Position = projection * view * model * position; 
}
