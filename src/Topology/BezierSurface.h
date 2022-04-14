#pragma once
#include "../Domain/Object.h"
#include "../Models/Icosphere.h"

class ControlPoint : public Object {
public:
	ControlPoint(int i, int j) {
		m_name = "Control Point " + std::to_string(i) + " " + std::to_string(j);
	}
	std::string getClassName() override;
	void update() override;
	void draw(const Window& window, const Camera& camera) override;
};

class BezierSurface : public Object {
public:
	BezierSurface();
	std::vector<ControlPoint*> setup(int pointsPerLine, int nbSubdivision);
	int getNbSubdivision() const {
		return m_subdivision;
	}
	std::string getClassName() override;
	void update() override;
	void draw(const Window& window, const Camera& camera) override;
	void addControlPoint(ControlPoint* point);
	void evaluate();
	glm::vec3 evaluate(float u, float v);

	ofMesh& getMesh() {
		return m_mesh;
	}

	void setNbSubdivision(int subdivision);
private:
	Icosphere* m_icosphere;
	std::vector<ControlPoint*> m_controlPoints;
	std::vector<glm::vec3> m_evaluatedPoints;

	glm::vec3 getPoint(int i, int j);

	float B(int i, int n, float u);
	int bernsteinPolynomial(int n, int i);
	long long factorial(long long n);
	
	int m_subdivision;
	int m_pointsPerLine;

	ofMesh m_mesh;
};
