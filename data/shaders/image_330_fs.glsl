#version 330

uniform sampler2D image;
uniform vec3 color;

in vec2 surface_texcoord;

out vec4 fragment_color;

void main()
{
  vec4 texture_sample = texture(image, surface_texcoord);
  texture_sample.x *= color.x;
  texture_sample.y *= color.y;
  texture_sample.z *= color.z;

  fragment_color = texture_sample;
}
