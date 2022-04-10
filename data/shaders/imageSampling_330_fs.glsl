#version 330

uniform sampler2D image1;
uniform sampler2D image2;

in vec2 surface_texcoord;

out vec4 fragment_color;

void main()
{
  vec4 texture_sample = texture(image2, surface_texcoord);
  fragment_color = texture_sample;
}
