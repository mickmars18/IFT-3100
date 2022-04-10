#include "Grid.h"

Grid::Grid() {
	m_shader.load("shaders/model_330_vs.glsl", "shaders/model_330_fs.glsl");

	int totalVertices = (m_nbDivision + 1) * (m_nbDivision + 1);
	m_vertices.reserve(totalVertices);
	for (size_t i = 0; i < m_nbDivision + 1; i++) {
		ofDefaultVertexType vertex(glm::vec3((float)i / (float)m_nbDivision * m_size, 0.0f, 0.0f));
		m_vertices.push_back(vertex);
	}
	m_transform.setPosition(-m_size / 2, 0.0f, m_size / 2);
}

std::string Grid::getClassName() {
	return "Grid";
}

void Grid::draw(const Window& window, const Camera& camera) {
	ofEnableDepthTest();
	m_shader.begin();
	m_shader.setUniformMatrix4f("modelview", camera.getViewMatrix() * getModel());
	m_shader.setUniformMatrix4f("projection", camera.getProjection());
	m_shader.setUniform4f("color", glm::vec4(0.5f, 0.5f, 0.5f, 0.5f));

	for (size_t i = 0; i < m_nbDivision + 1; i++) {
		ofDrawLine(m_vertices[i], m_vertices[i] - glm::vec3(0.0f, 0.0f, m_size));
	}
	for (size_t i = 0; i < m_nbDivision + 1; i++) {
		ofDrawLine(glm::vec3(0.0f, 0.0f, -m_vertices[i].x), glm::vec3(0.0f + m_size, 0.0f, -m_vertices[i].x));
	}

	m_shader.end();
	ofDisableDepthTest();
}

void Grid::update() {

}