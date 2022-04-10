#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <graphics/ofGraphicsConstants.h>
#include "Object.h"

class Grid : public Object {
public:
	Grid();
	std::string getClassName() override;
	void draw(const Window& window, const Camera& camera) override;
	void update() override;
private:
	float m_size = 2000.0f;
	int m_nbDivision = 40;
	std::vector<ofDefaultVertexType> m_vertices;

	ofShader m_shader;
};
