#include "Light.h"

Light::Light(LightMode lightMode) {
	m_lightGizmo = new LightGizmos();
	m_lightMode = lightMode;
	m_lightGizmo->setLightingMode(m_lightMode);

	m_diffuseColor = glm::vec3(1.0f, 1.0f, 1.0f);
	m_specularColor = glm::vec3(1.0f, 1.0f, 1.0f);

	if (lightMode == LightMode::Ambient)
		m_name = "Ambient light";
	else if (lightMode == LightMode::Directional)
		m_name = "Directional light";
	else if (lightMode == LightMode::Point)
		m_name = "Point light";
	else if (lightMode == LightMode::Spot)
		m_name = "Spot light";
}

std::string Light::getClassName() {
	return "Light";
}

void Light::update() {
	m_lightGizmo->setTransform(m_transform);
	m_lightGizmo->update();
}

void Light::draw(const Window& window, const Camera& camera) {
	drawLightGizmo(window, camera);
}

void Light::changeLightMode(LightMode lightMode) {
	m_lightMode = lightMode;
	m_lightGizmo->setLightingMode(lightMode);
}

glm::vec3 Light::getOrientation() {
	if (m_lightMode == LightMode::Spot || m_lightMode == LightMode::Directional) {
		glm::vec3 init(0.0f, 0.0f, -1.0f);
		init = glm::rotateX(init, ofDegToRad(getRotation().x));
		init = glm::rotateY(init, ofDegToRad(getRotation().y));
		init = glm::rotateZ(init, ofDegToRad(getRotation().z));
		return glm::normalize(init);
	}
	else {
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}
}

void Light::drawLightGizmo(const Window& window, const Camera& camera) {
	m_lightGizmo->draw(window, camera);
}

Light::~Light() {
	delete m_lightGizmo;
}