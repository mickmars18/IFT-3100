#pragma once

#include "ofMain.h"
#include "../Domain/Camera.h"

class Skybox {
public:
	Skybox();
	void setup(const std::vector<std::string>& faces);
	void draw(const Camera& camera);

private:
	unsigned int loadCubemap(std::vector<std::string> faces);
	void setSkyboxVAO();
	ofShader m_shader;
	GLuint m_cubemapTexture;
	unsigned int m_skyboxVAO;
};
