#version 330

in vec4 vertex_color;

out vec4 fragment_color;

void main()
{
  fragment_color = vertex_color;
}