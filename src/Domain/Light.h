#pragma once
#include "Object.h"
#include "../Models/Icosphere.h"
#include "../Models/LightGizmos.h"
#include "LightMode.h"

class Light : public Object {
public:
	Light(LightMode lightMode);
	~Light();
	std::string getClassName() override;
	void update() override;
	void draw(const Window& window, const Camera& camera) override;

	void changeLightMode(LightMode lightMode);

	void drawLightGizmo(const Window& window, const Camera& camera);

	void setIntensity(float intensity) { m_intensity = intensity; }
	float getIntensity() const { return m_intensity; }
	void setDiffuseColor(float r, float g, float b) { m_diffuseColor = glm::vec3(r, g, b); }
	void setSpecularColor(float r, float g, float b) { m_specularColor = glm::vec3(r, g, b); }

	glm::vec3 getDiffuseColor() const { return m_intensity * m_diffuseColor; }
	glm::vec3 getSpecularColor() const { return m_intensity * m_specularColor; }

	glm::vec3 getOrientation();

	LightMode getMode() const { return m_lightMode; }

private:
	LightGizmos* m_lightGizmo;
	LightMode m_lightMode;

	float m_intensity = 1.0f;
	glm::vec3 m_diffuseColor;
	glm::vec3 m_specularColor;
};
