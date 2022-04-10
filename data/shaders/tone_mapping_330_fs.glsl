#version 330

in vec2 surface_texcoord;
out vec4 fragment_color;

uniform sampler2D diffuse;
uniform float exposure;
uniform bool toggle;
uniform float gamma;

vec3 reinhard(vec3 x) {
  return x / (x + vec3(1.0));
}

vec3 ACESFilmic(vec3 x) {
    float a = 2.51f;
    float b = 0.03f;
    float c = 2.43f;
    float d = 0.59f;
    float e = 0.14f;
    return clamp((x * (a * x + b)) / (x * (c * x + d) + e), 0.0, 1.0);
}

void main() {
  vec3 texture_sample = texture(diffuse, surface_texcoord).rgb;

  texture_sample = pow(texture_sample, vec3(gamma));

  texture_sample = vec3(1.0) - exp(-texture_sample * exposure);

  if (toggle)
    texture_sample = ACESFilmic(texture_sample);
  else
    texture_sample = reinhard(texture_sample);

  texture_sample = pow(texture_sample, vec3(1.0 / gamma));

  fragment_color = vec4(texture_sample, 1.0);
}
