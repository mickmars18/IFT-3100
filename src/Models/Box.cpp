#include "Box.h"

RT_Box::RT_Box() {
	m_name = "Cube";
	m_shader.load("shaders/model_diffuse_330_vs.glsl", "shaders/model_diffuse_330_fs.glsl");

	for (size_t i = 0; i < 8; i++) {
		m_mesh.addVertex(ofPoint());
	}
}

void RT_Box::setBoxSize(float minX, float maxX, float minY, float maxY, float minZ, float maxZ) {
	m_mesh.setVertex(0, ofDefaultVertexType(minX, minY, minZ));
	m_mesh.setVertex(1, ofDefaultVertexType(maxX, minY, minZ));
	m_mesh.setVertex(2, ofDefaultVertexType(minX, maxY, minZ));
	m_mesh.setVertex(3, ofDefaultVertexType(maxX, maxY, minZ));
	m_mesh.setVertex(4, ofDefaultVertexType(minX, minY, maxZ));
	m_mesh.setVertex(5, ofDefaultVertexType(maxX, minY, maxZ));
	m_mesh.setVertex(6, ofDefaultVertexType(minX, maxY, maxZ));
	m_mesh.setVertex(7, ofDefaultVertexType(maxX, maxY, maxZ));
}

std::string RT_Box::getClassName() {
	return "Box";
}
void RT_Box::update() {

}

void RT_Box::draw(const Window& window, const Camera& camera) {
	ofEnableDepthTest();
	m_shader.begin();
	m_shader.setUniformMatrix4f("modelview", camera.getViewMatrix() * getModel());
	m_shader.setUniformMatrix4f("projection", camera.getProjection());
	m_shader.setUniform4f("color_diffuse", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	ofDrawLine(m_mesh.getVertex(0), m_mesh.getVertex(1));
	ofDrawLine(m_mesh.getVertex(1), m_mesh.getVertex(3));
	ofDrawLine(m_mesh.getVertex(0), m_mesh.getVertex(2));
	ofDrawLine(m_mesh.getVertex(2), m_mesh.getVertex(3));

	ofDrawLine(m_mesh.getVertex(4), m_mesh.getVertex(5));
	ofDrawLine(m_mesh.getVertex(5), m_mesh.getVertex(7));
	ofDrawLine(m_mesh.getVertex(7), m_mesh.getVertex(6));
	ofDrawLine(m_mesh.getVertex(6), m_mesh.getVertex(4));

	ofDrawLine(m_mesh.getVertex(1), m_mesh.getVertex(5));
	ofDrawLine(m_mesh.getVertex(3), m_mesh.getVertex(7));
	ofDrawLine(m_mesh.getVertex(0), m_mesh.getVertex(4));
	ofDrawLine(m_mesh.getVertex(2), m_mesh.getVertex(6));

	m_shader.end();
	ofDisableDepthTest();
}