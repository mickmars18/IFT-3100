#pragma once
#include "../Domain/Object.h"

class Line : public Object
{
public:
	Line(glm::vec3 point1, glm::vec3 point2);
	~Line();

	void setLinePosition(const glm::vec3& point1, const glm::vec3& point2) {
		m_mesh.setVertex(0, point1);
		m_mesh.setVertex(1, point2);
		m_mesh.setVertex(2, point1);
	}

	virtual std::string getClassName() override;
	virtual void update() override;
	virtual void draw(const Window& window, const Camera& camera) override;

private:
	ofMesh m_mesh;
	ofShader m_shader;
};
