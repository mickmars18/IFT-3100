#pragma once
#include "../Domain/Object.h"

class Cube : public Object {
public:
	Cube(float radius);
	std::string getClassName() override;
	void update() override;
	void draw(const Window& window, const Camera& camera) override;
private:
	ofMesh m_mesh;
};