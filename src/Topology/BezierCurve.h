#pragma once
#include "../Domain/Object.h"

class BezierCurve : public Object {
public:
	BezierCurve(const Window& window);
	~BezierCurve();
	std::string getClassName() override;
	void update() override;
	void draw(const Window& window, const Camera& camera) override;

	void mouseDragged(int x, int y);
	void mousePressed(int x, int y);
	void mouseReleased();

	glm::vec2 evaluate(float t);
private:
	glm::vec2 m_anchor0;
	glm::vec2 m_anchor1;
	glm::vec2 m_point0;
	glm::vec2 m_point1;
	glm::vec2 m_point2;

	bool m_anchor0Clicked = false;
	bool m_anchor1Clicked = false;
	bool m_point0Clicked = false;
	bool m_point1Clicked = false;
	bool m_point2Clicked = false;

	float m_pointRadius;
	ofPolyline m_polyline;

	int m_nbSubdivision = 100;
};
