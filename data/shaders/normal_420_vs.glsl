#version 420

#define MAX_LIGHTS 25

// attributs de sommet
in vec4 position;
in vec4 normal;
in vec2 texcoord;
in vec4 color; // tangente

// attributs en sortie
out vec3 surface_position;
out vec2 surface_texcoord;
out mat3 TBN;

// attributs uniformes
uniform mat4x4 modelview;
uniform mat4x4 model;
uniform mat4x4 projection;

void main()
{
  // calculer la matrice normale
  mat4x4 normalMatrix = transpose(inverse(model));

  // transformation de la normale du sommet dans l'espace de vue
  vec3 surface_normal = vec3(normalMatrix * normal);
  vec3 surface_tangent = vec3(normalMatrix * color);

  vec3 N = normalize(surface_normal);
  vec3 T = normalize(surface_tangent);
  T = normalize(T - dot(T, N) * N);
  vec3 B = cross(T, N);

  TBN = mat3(T, B, N);

  // transformation de la position du sommet dans l'espace de vue
  surface_position = vec3(modelview * position);

  // transformation de la position du sommet par les matrices de modèle, vue et projection
  gl_Position = projection * modelview * position;
  surface_texcoord = texcoord;
}