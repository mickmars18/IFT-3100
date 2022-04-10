#pragma once
#include "../Domain/Object.h"
#include "Box.h"

class Icosphere : public Object {
public:
	Icosphere(float radius, int nbSubdivision);
	std::string getClassName() override;
	void update() override;
	void draw(const Window& window, const Camera& camera) override;
	void increaseSubdivision();
	void decreaseSubdivision();
	int getSubdivision() const { return m_nbSubdivision; }
	int getMaxSubdivision() const { return m_maxSubdivision; }
private:
	ofMesh m_mesh;
	ofMesh m_meshCopy;
	int m_nbSubdivision = 0;
	float m_radius;
	int m_maxSubdivision = 6;

	void initializeIcopshereToZeroSubdivision();
	void subdivideIcosphere(int nbSubdivision);
	void subdivideIcosphere();
	void subdivideFace(int index1, int index2, int index3, int atVertex);
};
