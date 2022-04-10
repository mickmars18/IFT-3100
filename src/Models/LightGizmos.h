#pragma once
#include "../Domain/Object.h"
#include "../Domain/LightMode.h"

class LightGizmos : public Object {
public:
	LightGizmos();
	std::string getClassName() override;
	void update() override;
	void draw(const Window& window, const Camera& camera) override;

	void setLightingMode(LightMode lightMode);
private:
	void setDirectionalLightGizmo();
	void setPointLightGizmo();
	void setAmbientLightGizmo();
	void setSpotLightGizmo();

	ofMesh m_directionalLightMesh;
	ofMesh m_pointLightMesh;
	ofMesh m_ambientLightMesh;
	ofMesh m_spotLightMesh;

	float m_spotLightAngle = 60.0f;

	LightMode m_lightMode;
};
