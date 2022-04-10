#include "Line.h"

Line::Line(glm::vec3 point1, glm::vec3 point2) {
	m_shader.load("shaders/model_diffuse_330_vs.glsl", "shaders/model_diffuse_330_fs.glsl");

	m_mesh.addVertex(point1);
	m_mesh.addVertex(point2);
	m_mesh.addVertex(point1);

	m_mesh.addIndex(0);
	m_mesh.addIndex(1);
	m_mesh.addIndex(2);
}

std::string Line::getClassName() {
	return "Line";
}
void Line::update() {

}

void Line::draw(const Window& window, const Camera& camera) {
	ofEnableDepthTest();
	m_shader.begin();
	m_shader.setUniformMatrix4f("modelview", camera.getViewMatrix() * getModel());
	m_shader.setUniformMatrix4f("projection", camera.getProjection());
	m_shader.setUniform4f("color_diffuse", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	
	m_mesh.drawWireframe();

	m_shader.end();
	ofDisableDepthTest();
}

Line::~Line() {

}