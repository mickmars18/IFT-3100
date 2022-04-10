#include "LightGizmos.h"

LightGizmos::LightGizmos() {
	m_name = "LightGizmo";
	m_shader.load("shaders/model_diffuse_330_vs.glsl", "shaders/model_diffuse_330_fs.glsl");

	setDirectionalLightGizmo();
	setPointLightGizmo();
	setAmbientLightGizmo();
	setSpotLightGizmo();
}

void LightGizmos::setDirectionalLightGizmo() {
	float numberOfPointsInCircle = 24.0f;
	float radius = 10.0f;

	for (size_t i = 0; i < numberOfPointsInCircle; i++) {
		m_directionalLightMesh.addVertex(ofPoint(radius * sinf((float)i * 2.0f * PI / numberOfPointsInCircle),
			radius * cosf((float)i * 2.0f * PI / numberOfPointsInCircle),
			0.0f));
	}

	for (size_t i = 0; i < numberOfPointsInCircle - 1; i++) {
		m_directionalLightMesh.addIndex(i);
		m_directionalLightMesh.addIndex(i + 1);
		m_directionalLightMesh.addIndex(i);
	}

	m_directionalLightMesh.addIndex(numberOfPointsInCircle - 1);
	m_directionalLightMesh.addIndex(0);
	m_directionalLightMesh.addIndex(numberOfPointsInCircle - 1);

	float rayHeight = 30.0f;
	float numberOfRay = 5.0f;

	for (size_t i = 0; i < numberOfRay; i++) {
		int index = i * numberOfPointsInCircle / numberOfRay;
		ofDefaultVertexType vertex = m_directionalLightMesh.getVertex(index);
		vertex.z -= rayHeight;
		m_directionalLightMesh.addVertex(vertex);

		m_directionalLightMesh.addIndex(index);
		m_directionalLightMesh.addIndex(i + numberOfPointsInCircle);
		m_directionalLightMesh.addIndex(index);
	}
}

void LightGizmos::setPointLightGizmo() {
	float numberOfPointsInCircle = 24.0f;
	float radius = 6.0f;

	for (size_t i = 0; i < numberOfPointsInCircle; i++) {
		m_pointLightMesh.addVertex(ofPoint(radius * sinf((float)i * 2.0f * PI / numberOfPointsInCircle),
			0.0f,
			radius * cosf((float)i * 2.0f * PI / numberOfPointsInCircle)));
	}

	for (size_t i = 0; i < numberOfPointsInCircle - 1; i++) {
		m_pointLightMesh.addIndex(i);
		m_pointLightMesh.addIndex(i + 1);
		m_pointLightMesh.addIndex(i);
	}

	m_pointLightMesh.addIndex(numberOfPointsInCircle - 1);
	m_pointLightMesh.addIndex(0);
	m_pointLightMesh.addIndex(numberOfPointsInCircle - 1);

	for (size_t i = 0; i < numberOfPointsInCircle; i++) {
		m_pointLightMesh.addVertex(ofPoint(0.0f,
			radius * sinf((float)i * 2.0f * PI / numberOfPointsInCircle),
			radius * cosf((float)i * 2.0f * PI / numberOfPointsInCircle)));
	}

	for (size_t i = 0; i < numberOfPointsInCircle - 1; i++) {
		m_pointLightMesh.addIndex(numberOfPointsInCircle + i);
		m_pointLightMesh.addIndex(numberOfPointsInCircle + i + 1);
		m_pointLightMesh.addIndex(numberOfPointsInCircle + i);
	}

	m_pointLightMesh.addIndex(numberOfPointsInCircle + numberOfPointsInCircle - 1);
	m_pointLightMesh.addIndex(numberOfPointsInCircle);
	m_pointLightMesh.addIndex(numberOfPointsInCircle + numberOfPointsInCircle - 1);

	for (size_t i = 0; i < numberOfPointsInCircle; i++) {
		m_pointLightMesh.addVertex(ofPoint(radius * sinf((float)i * 2.0f * PI / numberOfPointsInCircle),
			radius * cosf((float)i * 2.0f * PI / numberOfPointsInCircle),
			0.0f));
	}

	for (size_t i = 0; i < numberOfPointsInCircle - 1; i++) {
		m_pointLightMesh.addIndex(2 * numberOfPointsInCircle + i);
		m_pointLightMesh.addIndex(2 * numberOfPointsInCircle + i + 1);
		m_pointLightMesh.addIndex(2 * numberOfPointsInCircle + i);
	}

	m_pointLightMesh.addIndex(2 * numberOfPointsInCircle + numberOfPointsInCircle - 1);
	m_pointLightMesh.addIndex(2 * numberOfPointsInCircle);
	m_pointLightMesh.addIndex(2 * numberOfPointsInCircle + numberOfPointsInCircle - 1);
}

void LightGizmos::setAmbientLightGizmo() {
	float numberOfPointsInCircle = 24.0f;
	float radius = 7.0f;

	for (size_t i = 0; i < numberOfPointsInCircle; i++) {
		m_ambientLightMesh.addVertex(ofPoint(radius * sinf((float)i * 2.0f * PI / numberOfPointsInCircle),
			radius * cosf((float)i * 2.0f * PI / numberOfPointsInCircle),
			0.0f));
	}

	for (size_t i = 0; i < numberOfPointsInCircle - 1; i++) {
		m_ambientLightMesh.addIndex(i);
		m_ambientLightMesh.addIndex(i + 1);
		m_ambientLightMesh.addIndex(i);
	}

	m_ambientLightMesh.addIndex(numberOfPointsInCircle - 1);
	m_ambientLightMesh.addIndex(0);
	m_ambientLightMesh.addIndex(numberOfPointsInCircle - 1);

	float numberOfRay = 8.0f;

	for (size_t i = 0; i < numberOfRay; i++) {
		int index = i * numberOfPointsInCircle / numberOfRay;
		ofDefaultVertexType vertex = m_ambientLightMesh.getVertex(index);
		vertex *= 2.0f;
		m_ambientLightMesh.addVertex(vertex);

		m_ambientLightMesh.addIndex(index);
		m_ambientLightMesh.addIndex(i + numberOfPointsInCircle);
		m_ambientLightMesh.addIndex(index);
	}
}

void LightGizmos::setSpotLightGizmo() {
	float numberOfPointsInCircle = 48.0f;

	float d = 50.0f;
	float x = d * tanf(ofDegToRad(m_spotLightAngle / 2.0f));

	ofPoint origin(0.0f, 0.0f, d);

	for (size_t i = 0; i < numberOfPointsInCircle; i++) {
		m_spotLightMesh.addVertex(ofPoint(x * sinf((float)i * 2.0f * PI / numberOfPointsInCircle),
			x * cosf((float)i * 2.0f * PI / numberOfPointsInCircle),
			d));
	}

	for (size_t i = 0; i < numberOfPointsInCircle - 1; i++) {
		m_spotLightMesh.addIndex(i);
		m_spotLightMesh.addIndex(i + 1);
		m_spotLightMesh.addIndex(i);
	}

	m_spotLightMesh.addIndex(numberOfPointsInCircle - 1);
	m_spotLightMesh.addIndex(0);
	m_spotLightMesh.addIndex(numberOfPointsInCircle - 1);

	m_spotLightMesh.addVertex(ofPoint(0.0f, 0.0f, 0.0f));

	int numberOfLines = 4;
	for (int i = 0; i < numberOfLines; i++) {
		m_spotLightMesh.addIndex(numberOfPointsInCircle);
		m_spotLightMesh.addIndex((float)i * (float)numberOfPointsInCircle / (float)numberOfLines);
		m_spotLightMesh.addIndex(numberOfPointsInCircle);
	}
}

std::string LightGizmos::getClassName() {
	return "LightGizmos";
}

void LightGizmos::update() {

}

void LightGizmos::draw(const Window& window, const Camera& camera) {
	ofEnableDepthTest();
	m_shader.begin();

	m_shader.setUniformMatrix4f("projection", camera.getProjection());
	m_shader.setUniform3f("color_diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
	m_shader.setUniformMatrix4f("modelview", camera.getViewMatrix() * getModel());

	glm::mat4 model;

	switch (m_lightMode) {
	case LightMode::Ambient:
		model = glm::inverse(glm::lookAt(getPosition(), camera.getPosition(), camera.getUp()));
		m_shader.setUniformMatrix4f("modelview", camera.getViewMatrix() * model);
		m_ambientLightMesh.drawWireframe();
		break;
	case LightMode::Directional:
		m_directionalLightMesh.drawWireframe();
		break;
	case LightMode::Point:
		m_pointLightMesh.drawWireframe();
		break;
	case LightMode::Spot:
		m_spotLightMesh.drawWireframe();
		break;
	default:
		break;
	}



	m_shader.end();
	ofDisableDepthTest();
}

void LightGizmos::setLightingMode(LightMode lightMode) {
	m_lightMode = lightMode;
}