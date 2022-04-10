#version 420

#define MAX_LIGHTS 25

// attributs interpolés à partir des valeurs en sortie du shader de sommet
in vec3 surface_position;
in vec3 surface_normal;
in vec2 surface_texcoord;
in mat3 TBN;

// attribut en sortie
out vec4 fragment_color;

//uniform sampler2D diffuse;
layout(binding = 0) uniform sampler2D diffuse;
layout(binding = 1) uniform sampler2D reflection;

uniform float tileX;
uniform float tileY;

// couleurs de réflexion du matériau
uniform vec3 color_ambient;
uniform vec3 color_diffuse;
uniform vec3 color_specular;

uniform vec4 ambientLights;

uniform int nbOfPointLights;
uniform vec3 pointLight_position[MAX_LIGHTS];
uniform vec4 pointLightDiffuseColor[MAX_LIGHTS];
uniform vec4 pointLightSpecularColor[MAX_LIGHTS];

uniform int nbOfDirectionalLights;
uniform vec4 directionalLightDiffuseColor[MAX_LIGHTS];
uniform vec4 directionalLightSpecularColor[MAX_LIGHTS];
uniform vec3 directionalLightOrientation[MAX_LIGHTS];

uniform int nbOfSpotLights;
uniform vec3 spotLight_position[MAX_LIGHTS];
uniform vec4 spotLightDiffuseColor[MAX_LIGHTS];
uniform vec4 spotLightSpecularColor[MAX_LIGHTS];
uniform vec3 spotLightOrientation[MAX_LIGHTS];

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
  vec4 ambientColor = ambientLights * vec4(color_ambient, 1.0f);
  vec4 diffuseColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
  vec4 specularColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);

  vec2 texCoord = vec2(surface_texcoord.x * tileX, surface_texcoord.y * tileY);

  vec3 n = normalize(surface_normal);

  // Point lights
  for(int i = 0; i < nbOfPointLights; i++) {
    vec3 l = normalize(pointLight_position[i] - surface_position);

    float reflection_diffuse = max(dot(n, l), 0.0f);

    float reflection_specular = 0.0;
    if (reflection_diffuse > 0.0)
    {
        vec3 v = normalize(-surface_position);
        vec3 r = reflect(-l, n);
        reflection_specular = pow(max(dot(v, r), 0.0f), shininess);
    }

    float pointAttenuation = pointLightAttenuation(pointLight_position[i], surface_position);

    diffuseColor += pointAttenuation * pointLightDiffuseColor[i] * vec4(color_diffuse, 1.0f) *
                texture(diffuse, texCoord) * reflection_diffuse;

    specularColor += pointAttenuation * pointLightSpecularColor[i] * vec4(color_specular, 1.0f)
                    * texture(reflection, texCoord) * reflection_specular;
  }

  // Directional lights
  for(int i = 0; i < nbOfDirectionalLights; i++) {
    float reflection_diffuse = max(dot(n, directionalLightOrientation[i]), 0.0f);

    float reflection_specular = 0.0f;
    if (reflection_diffuse > 0.0f)
    {
        vec3 v = normalize(-surface_position);
        vec3 r = reflect(-directionalLightOrientation[i], n);
        reflection_specular = pow(max(dot(v, r), 0.0f), shininess);
    }

    diffuseColor += directionalLightDiffuseColor[i] * vec4(color_diffuse, 1.0f) * 
                texture(diffuse, texCoord) * reflection_diffuse;

    specularColor += directionalLightSpecularColor[i] * vec4(color_specular, 1.0f)
                    * texture(reflection, texCoord) * reflection_specular;
  }

  // Spot lights
  for(int i = 0; i < nbOfSpotLights; i++) {
      vec3 l = normalize(spotLight_position[i] - surface_position);
      float reflection_diffuse = max(dot(n, l), 0.0f);

      float reflection_specular = 0.0;
      if (reflection_diffuse > 0.0)
      {
          vec3 v = normalize(-surface_position);
          vec3 r = reflect(-l, n);
          reflection_specular = pow(max(dot(v, r), 0.0f), shininess);
      }

      float spotAttenuation = spotLightAttenuation(spotLight_position[i], surface_position, -l, i);

      diffuseColor += spotAttenuation * spotLightDiffuseColor[i] * vec4(color_diffuse, 1.0f)
          * texture(diffuse, texCoord) * reflection_diffuse;

      specularColor += spotAttenuation * spotLightSpecularColor[i] * vec4(color_specular, 1.0f)
          * texture(reflection, texCoord) * reflection_specular;
  }

  fragment_color = ambientColor + diffuseColor + specularColor;                
}
