#pragma once
#include "../Domain/Object.h"

class RT_Box : public Object {
public:
	RT_Box();
	std::string getClassName() override;
	void update() override;
	void draw(const Window& window, const Camera& camera) override;
	void setBoxSize(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
private:
	ofMesh m_mesh;
};
