#include "PBR_Model.h"

PBR_Model::PBR_Model(const std::string& filename)
{
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

	m_shader.load("shaders/pbr_420_vs.glsl", "shaders/pbr_420_fs.glsl");
}

PBR_Model::PBR_Model(const PBR_Model& model) {
	m_name = model.m_name;
	m_mesh = model.m_mesh;
	m_meshCount = model.m_meshCount;
	m_material.setNumberOfMeshes(model.m_meshCount);

	for (unsigned int i = 0; i < m_meshCount; i++) {
		ofMaterial mat = model.m_importer.getMaterialForMesh(i);
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
}

std::string PBR_Model::getClassName() {
	return "PBR_Model";
}

void PBR_Model::update() {
	m_box.setTransform(getTransform());
}

void PBR_Model::draw(const Window& window, const Camera& camera) {
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

	m_shader.setUniform1f("material_brightness", m_material.getBrightness());
	m_shader.setUniform1f("material_metallic", m_material.getMetallic());
	m_shader.setUniform1f("material_roughness", m_material.getRoughness());
	m_shader.setUniform1f("material_occlusion", m_material.getOcclusion());
	m_shader.setUniform3f("material_fresnel_ior", m_material.getFresnel_ior());
	m_shader.setUniform1f("tone_mapping_exposure", m_material.getExposure());
	m_shader.setUniform1f("tone_mapping_gamma", m_material.getGamma());


	glm::vec3 light_position = m_lightsController->getPointLights()[0]->getPosition();
	glm::vec3 light_color = m_lightsController->getPointLights()[0]->getDiffuseColor();
	float light_intensity = m_lightsController->getPointLights()[0]->getIntensity();
	m_shader.setUniform3f("light_position", light_position);
	m_shader.setUniform3f("light_color", light_color);
	m_shader.setUniform1f("light_intensity", light_intensity);

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

	if (m_drawBox)
		m_box.draw(window, camera);
}