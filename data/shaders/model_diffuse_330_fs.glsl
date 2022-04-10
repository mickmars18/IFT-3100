#version 330

uniform vec3 color_diffuse;
in vec4 vertex_color;

out vec4 fragment_color;


void main()
{
  fragment_color = vec4(color_diffuse, 1.0f);
}
