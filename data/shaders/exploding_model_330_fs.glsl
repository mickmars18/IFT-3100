#version 330

uniform vec4 color_diffuse;

out vec4 fragment_color;

void main()
{
  fragment_color = color_diffuse;
}