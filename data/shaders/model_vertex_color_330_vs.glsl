#version 330

uniform mat4 modelview;
uniform mat4 projection;

in vec4 position;
in vec4 color;

out vec4 vertex_color;

void main()
{
  gl_Position = projection * modelview * position;
  vertex_color = color;
}