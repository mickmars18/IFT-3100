#version 330

uniform mat4 modelview;
uniform mat4 projection;
uniform vec3 vertexColor;

in vec4 position;
in vec3 color;

out vec3 vertex_color;

void main()
{
  vertex_color = color;
  gl_Position = projection * modelview * position;
}
