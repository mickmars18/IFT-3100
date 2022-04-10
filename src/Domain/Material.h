#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Texture.h"
#include "../Domain/Material.h"

class Material {
public:
	Material();
	void bindTextures(int i);
	void unbindTextures(int i);
	void setNumberOfMeshes(int count);
	void setAmbientColor(int i, const glm::vec3& color) { m_ambientColor[i] = color; }
	void setAllAmbientColor(const glm::vec3& color) {
		for (size_t i = 0; i < m_ambientColor.size(); i++) {
			m_ambientColor[i] = color;
		}
	}
	void setDiffuseColor(int i, const glm::vec3& color) { m_diffuseColor[i] = color; }
	void setSpecularColor(int i, const glm::vec3& color) { m_specularColor[i] = color; }
	void setShininess(int i, float shininess) { m_shininess[i] = shininess; }
	void setNormalMap(int i, Texture* normalMap) { m_normalMaps[i] = normalMap; };

	void setDiffuseTexture(int i, Texture* RT_Texture) { m_diffuseTextures[i] = RT_Texture; }
	void setAllDiffuseTextures(Texture* RT_Texture) {
		for (size_t i = 0; i < m_diffuseTextures.size(); i++) {
			m_diffuseTextures[i] = RT_Texture;
		}
	}

	void setReflectionTexture(int i, Texture* RT_Texture) { m_reflectionTextures[i] = RT_Texture; }
	void setAllReflectionTextures(Texture* RT_Texture) {
		for (size_t i = 0; i < m_diffuseTextures.size(); i++) {
			m_reflectionTextures[i] = RT_Texture;
		}
	}

	float getMetallic() const {
		return m_metallic;
	}
	float getRoughness() const {
		return m_roughness;
	}
	float getBrightness() const {
		return m_brightness;
	}
	float getOcclusion() const {
		return m_occlusion;
	}
	glm::vec3 getFresnel_ior() const {
		return m_fresnel_ior;
	}
	float getExposure() const {
		return m_exposure;
	}
	float getGamma() const {
		return m_gamma;
	}

	void setMetallic(float value) {
		m_metallic = value;
	}
	void setRoughness(float value) {
		m_roughness = value;
	}
	void setBrightness(float value) {
		m_brightness = value;
	}
	void setOcclusion(float value) {
		m_occlusion = value;
	}
	void setFresnel_ior(const glm::vec3& value) {
		m_fresnel_ior = value;
	}
	void setFresnelX_ior(float value) {
		m_fresnel_ior.x = value;
	}
	void setFresnelY_ior(float value) {
		m_fresnel_ior.y = value;
	}
	void setFresnelZ_ior(float value) {
		m_fresnel_ior.z = value;
	}
	void setExposure(float value) {
		m_exposure = value;
	}
	void setGamma(float value) {
		m_gamma = value;
	}
	void setMetallicTexture(int i, Texture* RT_Texture) { m_metallicTextures[i] = RT_Texture; }
	void setRoughnessTexture(int i, Texture* RT_Texture) { m_roughnessTextures[i] = RT_Texture; }
	void setOcclusionTexture(int i, Texture* RT_Texture) { m_occlusionTextures[i] = RT_Texture; }

	void resetAllColors();


	inline glm::vec3 getAmbientColor(int i) const { return m_ambientColor[i]; }
	inline glm::vec3 getDiffuseColor(int i) const { return m_diffuseColor[i]; }
	inline glm::vec3 getSpecularColor(int i) const { return m_specularColor[i]; }
	inline float getShininess(int i) const { return m_shininess[i]; }
	inline Texture* getDiffuseTexture(int i) const { return m_diffuseTextures[i]; }
	inline Texture* getReflectionTexture(int i) const { return m_reflectionTextures[i]; }
	inline Texture* getNormalMap(int i) const { return m_normalMaps[i]; }

private:
	std::vector<glm::vec3> m_ambientColor;
	std::vector<glm::vec3> m_diffuseColor;
	std::vector<glm::vec3> m_specularColor;

	std::vector<float> m_shininess;

	std::vector<Texture*> m_diffuseTextures;
	std::vector<Texture*> m_reflectionTextures;
	std::vector<Texture*> m_normalMaps;
	std::vector<Texture*> m_metallicTextures;
	std::vector<Texture*> m_roughnessTextures;
	std::vector<Texture*> m_occlusionTextures;

	glm::vec3 m_defaultAmbientColor;
	glm::vec3 m_defaultDiffuseColor;
	glm::vec3 m_defaultSpecularColor;
	float m_defaultShininess;

	float m_metallic = 1.0;
	float m_roughness = 1.0f;
	float m_brightness = 1.0f;
	float m_occlusion = 1.0f;
	glm::vec3 m_fresnel_ior = glm::vec3(0.04f, 0.04f, 0.04f);
	float m_exposure = 1.0f;
	float m_gamma = 2.2f;
};