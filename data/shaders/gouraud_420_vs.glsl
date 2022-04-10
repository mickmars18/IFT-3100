#version 420

#define MAX_LIGHTS 5

// attributs de sommet
in vec4 position;
in vec4 normal;
in vec2 texcoord;

// attributs en sortie
out vec3 surface_color;
out vec2 surface_texcoord;
out float pointLightReflection_diffuse[MAX_LIGHTS];
out float pointLightReflection_specular[MAX_LIGHTS];
out float directionalLightReflection_diffuse[MAX_LIGHTS];
out float directionalLightReflection_specular[MAX_LIGHTS];
out float spotLightReflection_diffuse[MAX_LIGHTS];
out float spotLightReflection_specular[MAX_LIGHTS];
out vec3 surface_ambient;

// attributs uniformes
uniform mat4x4 modelview;
uniform mat4x4 projection;

uniform int nbOfPointLights;
uniform vec3 pointLight_position[MAX_LIGHTS];

uniform int nbOfDirectionalLights;
uniform vec3 directionalLightOrientation[MAX_LIGHTS];

uniform int nbOfSpotLights;
uniform vec3 spotLight_position[MAX_LIGHTS];
uniform vec3 spotLightOrientation[MAX_LIGHTS];

// couleurs de réflexion du matériau
uniform vec3 color_diffuse;
uniform vec3 color_specular;

// facteur de brillance spéculaire du matériau
uniform float shininess;

float pointLightAttenuation(vec3 light_position, vec3 surface_position) {
    float d = distance(light_position, surface_position) / 100.0f;
    return 1.0f / (0.2f + d / 8.0f + pow(d, 2) / 64.0f);
}

float spotLightAttenuation(vec3 light_position, vec3 surface_position, vec3 i, int index) {
    float d = distance(light_position, surface_position) / 100.0f;
    int power = 5;
    float attenuation = pow(max(dot(spotLightOrientation[index], i), 0.0f), power);
    return attenuation / (0.2f + d / 8.0f + pow(d, 2) / 64.0f);;
}

void main()
{
  // calculer la matrice normale
  mat4x4 normalMatrix = transpose(inverse(modelview));

  // transformation de la normale du sommet dans l'espace de vue
  vec3 surface_normal = vec3(normalMatrix * normal);

  // transformation de la position du sommet dans l'espace de vue
  vec3 surface_position = vec3(modelview * position);

  // re-normaliser la normale
  vec3 n = normalize(surface_normal);

  // Point lights
  for(int i = 0; i < MAX_LIGHTS; i++) {
    vec3 l = normalize(pointLight_position[i] - surface_position);

    pointLightReflection_diffuse[i] = max(dot(n, l), 0.0f);

    pointLightReflection_specular[i] = 0.0;
    if (pointLightReflection_diffuse[i] > 0.0)
    {
        vec3 v = normalize(-surface_position);
        vec3 r = reflect(-l, n);
        pointLightReflection_specular[i] = pow(max(dot(v, r), 0.0), shininess);
    }

    float pointAttenuation = pointLightAttenuation(pointLight_position[i], surface_position);
    pointLightReflection_diffuse[i] *= pointAttenuation;
    pointLightReflection_specular[i] *= pointAttenuation;
  }

  // Directional lights
  for(int i = 0; i < MAX_LIGHTS; i++) {
    directionalLightReflection_diffuse[i] = max(dot(n, directionalLightOrientation[i]), 0.0f);

    directionalLightReflection_specular[i] = 0.0f;
    if (directionalLightReflection_diffuse[i] > 0.0f)
    {
        vec3 v = normalize(-surface_position);
        vec3 r = reflect(-directionalLightOrientation[i], n);
        directionalLightReflection_specular[i] = pow(max(dot(v, r), 0.0f), shininess);
    }
  }

  // Spot lights
  for(int i = 0; i < nbOfSpotLights; i++) {
      vec3 l = normalize(spotLight_position[i] - surface_position);
      spotLightReflection_diffuse[i] = max(dot(n, l), 0.0f);

      spotLightReflection_specular[i] = 0.0;
      if (spotLightReflection_diffuse[i] > 0.0)
      {
          vec3 v = normalize(-surface_position);
          vec3 r = reflect(-l, n);
          spotLightReflection_specular[i] = pow(max(dot(v, r), 0.0f), shininess);
      }

      float spotAttenuation = spotLightAttenuation(spotLight_position[i], surface_position, -l, i);

      spotLightReflection_diffuse[i] *= spotAttenuation;
      spotLightReflection_specular[i] *= spotAttenuation;
  }

  // transformation de la position du sommet par les matrices de modèle, vue et projection
  gl_Position = projection * modelview * position;
  surface_texcoord = texcoord;
}