#include "Model.h"
#include "../Helper/Log.h"
#include "ofLog.h"


Model::Model() {
	m_name = "Model";
	m_shader.load("shaders/phong_420_vs.glsl", "shaders/phong_420_fs.glsl");
}

Model::Model(const std::string& filename) {
	m_name = getFilenameFormatted(filename);

	m_mesh = m_importer.loadModel(filename);
	m_meshCount = m_mesh.size();
	m_material.setNumberOfMeshes(m_meshCount);

	for (unsigned int i = 0; i < m_meshCount; i++) {
		ofMaterial mat = m_importer.getMaterialForMesh(i);
		ofFloatColor ambientColor = mat.getAmbientColor();
		ofFloatColor diffuseColor = mat.getDiffuseColor();
		ofFloatColor specularColor = mat.getSpecularColor();

		m_material.setAmbientColor(i, glm::vec3(ambientColor.r, ambientColor.g, ambientColor.b));
		m_material.setDiffuseColor(i, glm::vec3(diffuseColor.r, diffuseColor.g, diffuseColor.b));
		m_material.setSpecularColor(i, glm::vec3(specularColor.r, specularColor.g, specularColor.b));
		m_material.setShininess(i, mat.getShininess());
	}

	scaleMeshes();
	setCentroid();
	m_transform.setOrigin(m_centroid);
	flipNormalsOnTheYAxis();

	m_shader.load("shaders/phong_420_vs.glsl", "shaders/phong_420_fs.glsl");
}

void Model::setLightsController(LightsController* lightController) {
	m_lightsController = lightController;

	m_positions = new glm::vec3[m_lightsController->getMaxNumberOfLights()];
	m_diffuseColors = new glm::vec4[m_lightsController->getMaxNumberOfLights()];
	m_specularColors = new glm::vec4[m_lightsController->getMaxNumberOfLights()];
	m_directions = new glm::vec3[m_lightsController->getMaxNumberOfLights()];
}

void Model::setGeometryShaders(const std::string& vs, const std::string& fs, const std::string& gs) {
	m_shader.unload();
	m_shader.load(vs, fs, gs);
	m_shader.printActiveAttributes();
}

void Model::scaleMeshes() {
	float max = getMaxVertexValue();
	ofDefaultVertexType vertex;
	for (unsigned int i = 0; i < m_meshCount; i++) {
		for (size_t j = 0; j < m_mesh[i]->getNumVertices(); j++) {
			vertex = m_mesh[i]->getVertex(j) * ofGetWindowWidth() / 4.0f / max;
			vertex.y *= -1.0f;
			m_mesh[i]->setVertex(j, vertex);
		}
	}
}

float Model::getMaxVertexValue() const {
	float max = 0.0f;
	for (unsigned int i = 0; i < m_meshCount; i++) {
		for (size_t j = 0; j < m_mesh[i]->getNumVertices(); j++) {
			if (abs(m_mesh[i]->getVertex(j).x) > max)
				max = abs(m_mesh[i]->getVertex(j).x);
			if (abs(m_mesh[i]->getVertex(j).y) > max)
				max = abs(m_mesh[i]->getVertex(j).y);
			if (abs(m_mesh[i]->getVertex(j).z) > max)
				max = abs(m_mesh[i]->getVertex(j).z);
		}
	}
	return max;
}

void Model::setCentroid() {
	float maxX = -1.0f * std::numeric_limits<float>::max();
	float maxY = -1.0f * std::numeric_limits<float>::max();
	float maxZ = -1.0f * std::numeric_limits<float>::max();
	float minX = std::numeric_limits<float>::max();
	float minY = std::numeric_limits<float>::max();
	float minZ = std::numeric_limits<float>::max();
	for (unsigned int i = 0; i < m_meshCount; i++) {
		for (size_t j = 0; j < m_mesh[i]->getNumVertices(); j++) {
			if (m_mesh[i]->getVertex(j).x > maxX)
				maxX = m_mesh[i]->getVertex(j).x;
			if (m_mesh[i]->getVertex(j).y > maxY)
				maxY = m_mesh[i]->getVertex(j).y;
			if (m_mesh[i]->getVertex(j).z > maxZ)
				maxZ = m_mesh[i]->getVertex(j).z;

			if (m_mesh[i]->getVertex(j).x < minX)
				minX = m_mesh[i]->getVertex(j).x;
			if (m_mesh[i]->getVertex(j).y < minY)
				minY = m_mesh[i]->getVertex(j).y;
			if (m_mesh[i]->getVertex(j).z < minZ)
				minZ = m_mesh[i]->getVertex(j).z;
		}
	}
	m_centroid = glm::vec3((maxX + minX) / 2.0f, (maxY + minY) / 2.0f, (maxZ + minZ) / 2.0f);
	m_box.setBoxSize(minX, maxX, minY, maxY, minZ, maxZ);
}

std::string Model::getClassName() {
	return "Model";
}

void Model::update() {
	m_box.setTransform(getTransform());
}

void Model::draw(const Window& window, const Camera& camera) {
	ofEnableDepthTest();
	m_shader.begin();
	m_shader.setUniformMatrix4f("model", getModel());
	m_shader.setUniformMatrix4f("modelview", camera.getViewMatrix() * getModel());
	m_shader.setUniformMatrix4f("projection", camera.getProjection());

	m_shader.setUniform1f("tileX", m_tileX);
	m_shader.setUniform1f("tileY", m_tileY);

	if (m_lightsController != nullptr) {
		m_shader.setUniform4f("ambientLights", glm::vec4(m_lightsController->getAmbiantLights(), 1.0f));
		setPointLightsUniforms(camera);
		setDirectionalLightsUniforms(camera);
		setSpotLightsUniforms(camera);
	}

	for (int i = 0; i < m_meshCount; i++) {
		
		if (m_wireFrameMode) {
			m_shader.setUniform4f("color_diffuse", glm::vec4(0.8f, 0.8f, 0.8f, 0.8f));
			m_mesh[i]->drawWireframe();
		}
		else {
			m_shader.setUniform3f("color_ambient", m_material.getAmbientColor(i));
			m_shader.setUniform3f("color_diffuse", m_material.getDiffuseColor(i));
			m_shader.setUniform3f("color_specular", m_material.getSpecularColor(i));
			float shininess = m_material.getShininess(i) * m_shininess;
			m_shader.setUniform1f("shininess", m_material.getShininess(i) * m_shininess);

			m_material.bindTextures(i);
			m_mesh[i]->draw();
			m_material.unbindTextures(i);
		}
	}
	m_shader.end();
	ofDisableDepthTest();

	if(m_drawBox)
		m_box.draw(window, camera);
}

void Model::setPointLightsUniforms(const Camera& camera) {
	std::vector<Light*> pointLights = m_lightsController->getPointLights();
	const int numberOfPointLights = pointLights.size();

	if (numberOfPointLights == 0) {
		m_shader.setUniform1i("nbOfPointLights", numberOfPointLights);
		return;
	}

	for (size_t i = 0; i < numberOfPointLights; i++) {
		m_positions[i] = camera.getViewMatrix() * glm::vec4(pointLights[i]->getPosition(), 1.0f);
		m_diffuseColors[i] = glm::vec4(pointLights[i]->getDiffuseColor(), 1.0f);
		m_specularColors[i] = glm::vec4(pointLights[i]->getSpecularColor(), 1.0f);
	}

	m_shader.setUniform3fv("pointLight_position", (const float*)m_positions, numberOfPointLights);
	m_shader.setUniform4fv("pointLightDiffuseColor", (const float*)m_diffuseColors, numberOfPointLights);
	m_shader.setUniform4fv("pointLightSpecularColor", (const float*)m_specularColors, numberOfPointLights);
	m_shader.setUniform1i("nbOfPointLights", numberOfPointLights);
	m_shader.setUniform1i("nbOfPointLights_vs", numberOfPointLights);
}

void Model::setDirectionalLightsUniforms(const Camera& camera) {
	std::vector<Light*> directionalLights = m_lightsController->getDirectionalLights();
	const int numberOfDirectionalLights = directionalLights.size();

	if (numberOfDirectionalLights == 0) {
		m_shader.setUniform1i("nbOfDirectionalLights", numberOfDirectionalLights);
		return;
	}

	for (size_t i = 0; i < numberOfDirectionalLights; i++) {
		m_diffuseColors[i] = glm::vec4(directionalLights[i]->getDiffuseColor(), 1.0f);
		m_specularColors[i] = glm::vec4(directionalLights[i]->getSpecularColor(), 1.0f);
		m_directions[i] = -1.0f * directionalLights[i]->getOrientation();
	}

	m_shader.setUniform4fv("directionalLightDiffuseColor", (const float*)m_diffuseColors, numberOfDirectionalLights);
	m_shader.setUniform4fv("directionalLightSpecularColor", (const float*)m_specularColors, numberOfDirectionalLights);
	m_shader.setUniform3fv("directionalLightOrientation", (const float*)m_directions, numberOfDirectionalLights);
	m_shader.setUniform1i("nbOfDirectionalLights", numberOfDirectionalLights);
}

void Model::setSpotLightsUniforms(const Camera& camera) {
	std::vector<Light*> spotLights = m_lightsController->getSpotLights();
	const int numberOfSpotLights = spotLights.size();

	if (numberOfSpotLights == 0) {
		m_shader.setUniform1i("nbOfSpotLights", numberOfSpotLights);
		return;
	}

	for (size_t i = 0; i < numberOfSpotLights; i++) {
		m_positions[i] = camera.getViewMatrix() * glm::vec4(spotLights[i]->getPosition(), 1.0f);
		m_diffuseColors[i] = glm::vec4(spotLights[i]->getDiffuseColor(), 1.0f);
		m_specularColors[i] = glm::vec4(spotLights[i]->getSpecularColor(), 1.0f);
		m_directions[i] = -1.0f * spotLights[i]->getOrientation();
	}

	m_shader.setUniform3fv("spotLight_position", (const float*)m_positions, numberOfSpotLights);
	m_shader.setUniform4fv("spotLightDiffuseColor", (const float*)m_diffuseColors, numberOfSpotLights);
	m_shader.setUniform4fv("spotLightSpecularColor", (const float*)m_specularColors, numberOfSpotLights);
	m_shader.setUniform3fv("spotLightOrientation", (const float*)m_directions, numberOfSpotLights);
	m_shader.setUniform1i("nbOfSpotLights", numberOfSpotLights);
}

void Model::setColorsFromLoadedMaterial() {
	for (unsigned int i = 0; i < m_meshCount; i++) {
		ofMaterial mat = m_importer.getMaterialForMesh(i);
		ofFloatColor ambientColor = mat.getAmbientColor();
		ofFloatColor diffuseColor = mat.getDiffuseColor();
		ofFloatColor specularColor = mat.getSpecularColor();

		m_material.setAmbientColor(i, glm::vec3(ambientColor.r, ambientColor.g, ambientColor.b));
		m_material.setDiffuseColor(i, glm::vec3(diffuseColor.r, diffuseColor.g, diffuseColor.b));
		m_material.setSpecularColor(i, glm::vec3(specularColor.r, specularColor.g, specularColor.b));
		m_material.setShininess(i, mat.getShininess());
	}
}

void Model::resetAllColors() {
	m_material.resetAllColors();
}

void Model::flipNormalsOnTheYAxis() {
	for (unsigned int i = 0; i < m_meshCount; i++) {
		for (size_t j = 0; j < m_mesh[i]->getNumVertices(); j++) {
			ofDefaultNormalType normal = m_mesh[i]->getNormal(j);
			normal.y *= -1.0f;
			m_mesh[i]->setNormal(j, normal);
		}
	}
}

Model::~Model() {
	if(m_positions != nullptr)
		delete[] m_positions;
	if(m_diffuseColors != nullptr)
		delete[] m_diffuseColors;
	if(m_specularColors != nullptr)
		delete[] m_specularColors;
	if (m_directions != nullptr)
		delete[] m_directions;
}