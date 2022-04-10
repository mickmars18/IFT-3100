#include "Plane.h"

Plane::Plane(int sizeX, int sizeY, Texture* RT_Texture) :
	m_sizeX(sizeX), m_sizeY(sizeY), m_texture(RT_Texture)
{
	m_name = "Plane";
	m_shader.load("shaders/model_330_vs.glsl", "shaders/model_330_fs.glsl");

	m_mesh.addVertex(ofPoint(-sizeX / 2, -sizeY / 2, 0.0f));
	m_mesh.addTexCoord(glm::vec2(0.0f, 0.0f));

	m_mesh.addVertex(ofPoint(sizeX / 2, -sizeY / 2, 0.0f));
	m_mesh.addTexCoord(glm::vec2(1.0f, 0.0f));

	m_mesh.addVertex(ofPoint(-sizeX / 2, sizeY / 2, 0.0f));
	m_mesh.addTexCoord(glm::vec2(0.0f, 1.0f));

	m_mesh.addVertex(ofPoint(sizeX / 2, sizeY / 2, 0.0f));
	m_mesh.addTexCoord(glm::vec2(1.0f, 1.0f));


	m_mesh.addIndex(0);
	m_mesh.addIndex(1);
	m_mesh.addIndex(2);
	m_mesh.addIndex(1);
	m_mesh.addIndex(2);
	m_mesh.addIndex(3);
}

void Plane::changeShaders(const std::string& vs, const std::string& fs) {
	m_shader.unload();
	m_shader.load(vs, fs);
}

void Plane::setTexture(Texture* RT_Texture) {
	m_texture = RT_Texture;
}

std::string Plane::getClassName() {
	return "Plane";
}

void Plane::update() {

}

void Plane::draw(const Window& window, const Camera& camera) {
	ofEnableDepthTest();
	m_shader.begin();
	m_shader.setUniformMatrix4f("modelview", camera.getViewMatrix() * getModel());
	m_shader.setUniformMatrix4f("projection", camera.getProjection());
	m_shader.setUniform4f("color_diffuse", glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));

	m_shader.setUniform1i("toggle", m_toggle);
	m_shader.setUniform1f("gamma", m_gamma);
	m_shader.setUniform1f("exposure", m_exposure);

	if (m_wireFrameMode)
		m_mesh.drawWireframe();
	else {
		if (m_texture != nullptr) {
			m_texture->bind(0);
		}

		m_mesh.draw();

		if (m_texture != nullptr) {
			m_texture->unbind(0);
		}
	}

	m_shader.end();
	ofDisableDepthTest();
}