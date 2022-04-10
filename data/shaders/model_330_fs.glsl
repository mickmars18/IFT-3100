#version 330

uniform sampler2D diffuse;
uniform vec4 color_diffuse;

in vec2 surface_texcoord;

out vec4 fragment_color;

void main()
{
  fragment_color = texture(diffuse, surface_texcoord) * color_diffuse;
}
