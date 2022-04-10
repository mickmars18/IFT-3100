#include "Material.h"

Material::Material() {
	m_defaultAmbientColor = glm::vec3(0.0f, 0.0f, 0.0f);
	m_defaultDiffuseColor = glm::vec3(1.0f, 1.0f, 1.0f);
	m_defaultSpecularColor = glm::vec3(1.0f, 1.0f, 1.0f);
	m_defaultShininess = 5.0f;
}

void Material::resetAllColors() {
	for (int i = 0; i < m_ambientColor.size(); i++) {
		m_ambientColor[i] = m_defaultAmbientColor;
	}
	for (int i = 0; i < m_diffuseColor.size(); i++) {
		m_diffuseColor[i] = m_defaultDiffuseColor;
	}
	for (int i = 0; i < m_specularColor.size(); i++) {
		m_specularColor[i] = m_defaultSpecularColor;
	}
	for (int i = 0; i < m_shininess.size(); i++) {
		m_shininess[i] = m_defaultShininess;
	}
}

void Material::bindTextures(int i) {
	if (m_diffuseTextures[i] != nullptr)
		m_diffuseTextures[i]->bind(0);

	if (m_reflectionTextures[i] != nullptr)
		m_reflectionTextures[i]->bind(1);

	if (m_metallicTextures[i] != nullptr)
		m_metallicTextures[i]->bind(1);

	if (m_normalMaps[i] != nullptr)
		m_normalMaps[i]->bind(2);

	if (m_roughnessTextures[i] != nullptr)
		m_roughnessTextures[i]->bind(3);

	if (m_occlusionTextures[i] != nullptr)
		m_occlusionTextures[i]->bind(4);
}

void Material::unbindTextures(int i) {
	if (m_diffuseTextures[i] != nullptr)
		m_diffuseTextures[i]->unbind(0);

	if (m_reflectionTextures[i] != nullptr)
		m_reflectionTextures[i]->unbind(1);

	if (m_metallicTextures[i] != nullptr)
		m_metallicTextures[i]->unbind(1);

	if (m_normalMaps[i] != nullptr)
		m_normalMaps[i]->unbind(2);

	if (m_roughnessTextures[i] != nullptr)
		m_roughnessTextures[i]->unbind(3);

	if (m_occlusionTextures[i] != nullptr)
		m_occlusionTextures[i]->unbind(4);
}

void Material::setNumberOfMeshes(int count) {
	m_ambientColor.clear();
	m_diffuseColor.clear();
	m_specularColor.clear();
	m_shininess.clear();
	m_diffuseTextures.clear();

	for (int i = 0; i < count; i++) {
		m_ambientColor.push_back(m_defaultAmbientColor);
		m_diffuseColor.push_back(m_defaultDiffuseColor);
		m_specularColor.push_back(m_defaultSpecularColor);
		m_shininess.push_back(m_defaultShininess);
		m_diffuseTextures.push_back(nullptr);
		m_reflectionTextures.push_back(nullptr);
		m_normalMaps.push_back(nullptr);
		m_metallicTextures.push_back(nullptr);
		m_roughnessTextures.push_back(nullptr);
		m_occlusionTextures.push_back(nullptr);
	}
}