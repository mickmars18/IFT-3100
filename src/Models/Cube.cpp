#include "Cube.h"

Cube::Cube(float radius) {
	m_name = "Cube";
	m_shader.load("shaders/model_diffuse_330_vs.glsl", "shaders/model_diffuse_330_fs.glsl");

	m_mesh.addVertex(ofPoint(-radius, -radius, radius));
	m_mesh.addVertex(ofPoint(radius, -radius, radius));
	m_mesh.addVertex(ofPoint(-radius, radius, radius));
	m_mesh.addVertex(ofPoint(radius, radius, radius));

	m_mesh.addVertex(ofPoint(-radius, -radius, -radius));
	m_mesh.addVertex(ofPoint(radius, -radius, -radius));
	m_mesh.addVertex(ofPoint(-radius, radius, -radius));
	m_mesh.addVertex(ofPoint(radius, radius, -radius));

	m_mesh.addIndex(0);
	m_mesh.addIndex(1);
	m_mesh.addIndex(2);
	m_mesh.addIndex(1);
	m_mesh.addIndex(2);
	m_mesh.addIndex(3);
	
	m_mesh.addIndex(0);
	m_mesh.addIndex(4);
	m_mesh.addIndex(1);
	m_mesh.addIndex(1);
	m_mesh.addIndex(4);
	m_mesh.addIndex(5);

	m_mesh.addIndex(1);
	m_mesh.addIndex(5);
	m_mesh.addIndex(7);
	m_mesh.addIndex(1);
	m_mesh.addIndex(7);
	m_mesh.addIndex(3);

	m_mesh.addIndex(6);
	m_mesh.addIndex(2);
	m_mesh.addIndex(3);
	m_mesh.addIndex(6);
	m_mesh.addIndex(3);
	m_mesh.addIndex(7);

	m_mesh.addIndex(4);
	m_mesh.addIndex(0);
	m_mesh.addIndex(6);
	m_mesh.addIndex(0);
	m_mesh.addIndex(2);
	m_mesh.addIndex(6);

	m_mesh.addIndex(5);
	m_mesh.addIndex(4);
	m_mesh.addIndex(6);
	m_mesh.addIndex(5);
	m_mesh.addIndex(6);
	m_mesh.addIndex(7);
}

std::string Cube::getClassName() {
	return "Cube";
}

void Cube::update() {

}

void Cube::draw(const Window& window, const Camera& camera) {
	ofEnableDepthTest();
	m_shader.begin();
	m_shader.setUniformMatrix4f("modelview", camera.getViewMatrix() * getModel());
	m_shader.setUniformMatrix4f("projection", camera.getProjection());
	m_shader.setUniform3f("color_diffuse", glm::vec3(0.7f, 0.7f, 0.7f));

	if(m_wireFrameMode)
		m_mesh.drawWireframe();
	else
		m_mesh.draw();

	m_shader.end();
	ofDisableDepthTest();
}