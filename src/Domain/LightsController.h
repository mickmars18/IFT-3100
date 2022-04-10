#pragma once
#include "Light.h"
#include <set>

class LightsController {
public:
	LightsController();

	void addLight(Light* light);
	void removeLight(Light* light);

	std::vector<Light*> getPointLights();
	std::vector<Light*> getDirectionalLights();
	std::vector<Light*> getSpotLights();

	void changeLightMode(Light* light, LightMode newLightMode);

	glm::vec3 getAmbiantLights();

	int getMaxNumberOfLights() const { return m_maxNumberOfLights; }

	void clear();
private:
	void addAmbientLight(Light* light);
	void addDirectionalLight(Light* light);
	void addPointLight(Light* light);
	void addSpotLight(Light* light);

	void removeAmbientLight(Light* light);
	void removeDirectionalLight(Light* light);
	void removePointLight(Light* light);
	void removeSpotLight(Light* light);

	std::vector<Light*> m_ambientLights;
	std::vector<Light*> m_directionalLights;
	std::vector<Light*> m_pointLights;
	std::vector<Light*> m_spotLights;

	int m_maxNumberOfLights = 25;
};
