#version 330

uniform mat4 modelview;
uniform mat4 projection;

in vec4 position;
in vec2 texcoord;

out vec2 surface_texcoord;

void main()
{
  gl_Position = projection * modelview * position;

  surface_texcoord = texcoord;
}
