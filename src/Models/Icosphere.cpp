#include "Icosphere.h"

Icosphere::Icosphere(float radius, int nbSubdivision) {
	m_name = "Icosphere";
	m_shader.load("shaders/model_diffuse_330_vs.glsl", "shaders/model_diffuse_330_fs.glsl");
	m_radius = radius;
	subdivideIcosphere(nbSubdivision);
}

void Icosphere::increaseSubdivision() {
	subdivideIcosphere(m_nbSubdivision + 1);
}

void Icosphere::decreaseSubdivision() {
	subdivideIcosphere(m_nbSubdivision - 1);
}

void Icosphere::subdivideIcosphere(int nbSubdivision) {
	nbSubdivision = CLAMP(nbSubdivision, 0, m_maxSubdivision);
	initializeIcopshereToZeroSubdivision();
	m_nbSubdivision = nbSubdivision;

	for (int i = 0; i < nbSubdivision; i++) {
		subdivideIcosphere();
	}

	for (size_t i = 0; i < m_mesh.getNumVertices(); i++) {
		m_mesh.setVertex(i, m_mesh.getVertex(i) * m_radius);
	}
}

void Icosphere::subdivideIcosphere() {
	m_meshCopy.clear();
	m_meshCopy = m_mesh;
	m_mesh.clear();
	for (size_t i = 0; i < m_meshCopy.getNumIndices() / 3; i++) {
		subdivideFace(m_meshCopy.getIndex(i * 3), m_meshCopy.getIndex(1 + i * 3), m_meshCopy.getIndex(2 + i * 3), 6 * i);
	}
}

void Icosphere::subdivideFace(int index0, int index1, int index2, int atVertex) {
	ofDefaultVertexType vertex0 = m_meshCopy.getVertex(index0);
	ofDefaultVertexType vertex1 = m_meshCopy.getVertex(index1);
	ofDefaultVertexType vertex2 = m_meshCopy.getVertex(index2);
	ofDefaultVertexType vertex3 = (vertex0 + vertex1) / 2.0f;
	ofDefaultVertexType vertex4 = (vertex1 + vertex2) / 2.0f;
	ofDefaultVertexType vertex5 = (vertex0 + vertex2) / 2.0f;

	vertex3 = ofVec3f(vertex3.x, vertex3.y, vertex3.z).normalize();
	vertex4 = ofVec3f(vertex4.x, vertex4.y, vertex4.z).normalize();
	vertex5 = ofVec3f(vertex5.x, vertex5.y, vertex5.z).normalize();

	m_mesh.addVertex(vertex0);
	m_mesh.addVertex(vertex1);
	m_mesh.addVertex(vertex2);
	m_mesh.addVertex(vertex3);
	m_mesh.addVertex(vertex4);
	m_mesh.addVertex(vertex5);

	m_mesh.addIndex(0 + atVertex);
	m_mesh.addIndex(3 + atVertex);
	m_mesh.addIndex(5 + atVertex);

	m_mesh.addIndex(3 + atVertex);
	m_mesh.addIndex(1 + atVertex);
	m_mesh.addIndex(4 + atVertex);

	m_mesh.addIndex(5 + atVertex);
	m_mesh.addIndex(4 + atVertex);
	m_mesh.addIndex(2 + atVertex);

	m_mesh.addIndex(3 + atVertex);
	m_mesh.addIndex(4 + atVertex);
	m_mesh.addIndex(5 + atVertex);
}

std::string Icosphere::getClassName() {
	return "Icosphere";
}

void Icosphere::update() {

}

void Icosphere::draw(const Window& window, const Camera& camera) {
	ofEnableDepthTest();
	m_shader.begin();
	m_shader.setUniformMatrix4f("modelview", camera.getViewMatrix() * getModel());
	m_shader.setUniformMatrix4f("projection", camera.getProjection());
	m_shader.setUniform3f("color_diffuse", glm::vec3(0.8f, 0.8f, 0.8f));

	if (m_wireFrameMode)
		m_mesh.drawWireframe();
	else
		m_mesh.draw();

	m_shader.end();
	ofDisableDepthTest();
}

void Icosphere::initializeIcopshereToZeroSubdivision() {
	m_mesh.clear();

	const float X = 0.525731112119133606f;
	const float t = 0.850650808352039932f;
	const float N = 0.0f;

	m_mesh.addVertex(ofPoint(-X, t, N));
	m_mesh.addVertex(ofPoint(X, t, N));
	m_mesh.addVertex(ofPoint(-X, -t, N));
	m_mesh.addVertex(ofPoint(X, -t, N));

	m_mesh.addVertex(ofPoint(N, -X, t));
	m_mesh.addVertex(ofPoint(N, X, t));
	m_mesh.addVertex(ofPoint(N, -X, -t));
	m_mesh.addVertex(ofPoint(N, X, -t));

	m_mesh.addVertex(ofPoint(t, N, -X));
	m_mesh.addVertex(ofPoint(t, N, X));
	m_mesh.addVertex(ofPoint(-t, N, -X));
	m_mesh.addVertex(ofPoint(-t, N, X));

	m_mesh.addIndex(0);
	m_mesh.addIndex(11);
	m_mesh.addIndex(5);

	m_mesh.addIndex(0);
	m_mesh.addIndex(5);
	m_mesh.addIndex(1);

	m_mesh.addIndex(0);
	m_mesh.addIndex(1);
	m_mesh.addIndex(7);

	m_mesh.addIndex(0);
	m_mesh.addIndex(7);
	m_mesh.addIndex(10);

	m_mesh.addIndex(0);
	m_mesh.addIndex(10);
	m_mesh.addIndex(11);

	m_mesh.addIndex(1);
	m_mesh.addIndex(5);
	m_mesh.addIndex(9);

	m_mesh.addIndex(5);
	m_mesh.addIndex(11);
	m_mesh.addIndex(4);

	m_mesh.addIndex(11);
	m_mesh.addIndex(10);
	m_mesh.addIndex(2);

	m_mesh.addIndex(10);
	m_mesh.addIndex(7);
	m_mesh.addIndex(6);

	m_mesh.addIndex(7);
	m_mesh.addIndex(1);
	m_mesh.addIndex(8);

	m_mesh.addIndex(3);
	m_mesh.addIndex(9);
	m_mesh.addIndex(4);

	m_mesh.addIndex(3);
	m_mesh.addIndex(4);
	m_mesh.addIndex(2);

	m_mesh.addIndex(3);
	m_mesh.addIndex(2);
	m_mesh.addIndex(6);

	m_mesh.addIndex(3);
	m_mesh.addIndex(6);
	m_mesh.addIndex(8);

	m_mesh.addIndex(3);
	m_mesh.addIndex(8);
	m_mesh.addIndex(9);

	m_mesh.addIndex(4);
	m_mesh.addIndex(9);
	m_mesh.addIndex(5);

	m_mesh.addIndex(2);
	m_mesh.addIndex(4);
	m_mesh.addIndex(11);

	m_mesh.addIndex(6);
	m_mesh.addIndex(2);
	m_mesh.addIndex(10);

	m_mesh.addIndex(8);
	m_mesh.addIndex(6);
	m_mesh.addIndex(7);

	m_mesh.addIndex(9);
	m_mesh.addIndex(8);
	m_mesh.addIndex(1);
}