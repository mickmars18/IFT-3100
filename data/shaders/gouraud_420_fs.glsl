#version 420

#define MAX_LIGHTS 5

// attribut interpolé à partir des valeurs en sortie du shader de sommet
in vec3 surface_color;
in vec2 surface_texcoord;

in float pointLightReflection_diffuse[MAX_LIGHTS];
in float pointLightReflection_specular[MAX_LIGHTS];
in float directionalLightReflection_diffuse[MAX_LIGHTS];
in float directionalLightReflection_specular[MAX_LIGHTS];
in float spotLightReflection_diffuse[MAX_LIGHTS];
in float spotLightReflection_specular[MAX_LIGHTS];

uniform int nbOfPointLights;
uniform vec4 pointLightDiffuseColor[MAX_LIGHTS];
uniform vec4 pointLightSpecularColor[MAX_LIGHTS];

uniform int nbOfDirectionalLights;
uniform vec4 directionalLightDiffuseColor[MAX_LIGHTS];
uniform vec4 directionalLightSpecularColor[MAX_LIGHTS];

uniform int nbOfSpotLights;
uniform vec4 spotLightDiffuseColor[MAX_LIGHTS];
uniform vec4 spotLightSpecularColor[MAX_LIGHTS];

uniform vec3 color_ambient;
uniform vec3 color_diffuse;
uniform vec3 color_specular;

uniform vec4 ambientLights;

layout(binding = 0) uniform sampler2D diffuse;
layout(binding = 1) uniform sampler2D reflection;

// attribut en sortie
out vec4 fragment_color;

void main()
{
    vec4 ambientColor = ambientLights * vec4(color_ambient, 1.0f);
    vec4 diffuseColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    vec4 specularColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);

    for(int i = 0; i < nbOfPointLights; i++) {
        diffuseColor += pointLightDiffuseColor[i] * vec4(color_diffuse, 1.0f)
            * texture(diffuse, surface_texcoord) * pointLightReflection_diffuse[i];

        specularColor += pointLightSpecularColor[i] * vec4(color_specular, 1.0f)
            * texture(reflection, surface_texcoord) * pointLightReflection_specular[i];
    }

    for(int i = 0; i < nbOfDirectionalLights; i++) {
        diffuseColor += directionalLightDiffuseColor[i] * vec4(color_diffuse, 1.0f)
            * texture(diffuse, surface_texcoord) * directionalLightReflection_diffuse[i];

        specularColor += directionalLightSpecularColor[i] * vec4(color_specular, 1.0f)
            * texture(reflection, surface_texcoord) * directionalLightReflection_specular[i];
    }

    for(int i = 0; i < nbOfSpotLights; i++) {
        diffuseColor += spotLightDiffuseColor[i] * vec4(color_diffuse, 1.0f)
            * texture(diffuse, surface_texcoord) * spotLightReflection_diffuse[i];

        specularColor += spotLightSpecularColor[i] * vec4(color_specular, 1.0f)
            * texture(reflection, surface_texcoord) * spotLightReflection_specular[i];
    }

    fragment_color = ambientColor + diffuseColor + specularColor;
}