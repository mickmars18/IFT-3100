#include "BezierCurve.h"

BezierCurve::BezierCurve(const Window& window) :
	m_pointRadius(8.0f)
{
	m_name = "Bezier Curve";

	float padding = 50.0f;
	m_anchor0 = glm::vec2(padding, ofGetWindowHeight() / 2.0);
	m_anchor1 = glm::vec2(window.getWidth() - padding, window.getHeight() / 2.0);
	m_point0 = glm::vec2(padding + (window.getWidth() - 2 * padding) / 4, 3.0f * window.getHeight() / 4.0f);
	m_point1 = glm::vec2(padding + 2.0f * (window.getWidth() - 2 * padding) / 4, window.getHeight() / 4.0f);
	m_point2 = glm::vec2(padding + 3.0f * (window.getWidth() - 2 * padding) / 4, 3.0f * window.getHeight() / 4.0f);
}

std::string BezierCurve::getClassName() {
	return "BezierCurve";
}

void BezierCurve::update() {
	m_polyline.clear();
	glm::vec2 lastEval = evaluate(0.0f);

	m_polyline.addVertex(lastEval.x, lastEval.y, 0);

	for (int i = 1; i < m_nbSubdivision + 1; i++) {
		float t = (float)i / (float)m_nbSubdivision;
		glm::vec2 newEval = evaluate(t);
		m_polyline.addVertex(newEval.x, newEval.y, 0);
		lastEval = newEval;
	}
}

glm::vec2 BezierCurve::evaluate(float t) {
	glm::vec2 result(0.0f, 0.0f);
	result += pow(1.0f - t, 4) * m_anchor0;
	result += 4 * pow(1.0f - t, 3) * t * m_point0;
	result += 6 * pow(1.0f - t, 2) * pow(t, 2) * m_point1;
	result += 4 * (1.0f - t) * pow(t, 3) * m_point2;
	result += pow(t, 4) * m_anchor1;
	return result;
}

void BezierCurve::mousePressed(int x, int y) {
	float distance = glm::distance(glm::vec2(x, y), m_anchor0);
	if (distance <= m_pointRadius) {
		m_anchor0Clicked = true;
		return;
	}
	distance = glm::distance(glm::vec2(x, y), m_anchor1);
	if (distance <= m_pointRadius) {
		m_anchor1Clicked = true;
		return;
	}
	distance = glm::distance(glm::vec2(x, y), m_point0);
	if (distance <= m_pointRadius) {
		m_point0Clicked = true;
		return;
	}
	distance = glm::distance(glm::vec2(x, y), m_point1);
	if (distance <= m_pointRadius) {
		m_point1Clicked = true;
		return;
	}
	distance = glm::distance(glm::vec2(x, y), m_point2);
	if (distance <= m_pointRadius) {
		m_point2Clicked = true;
		return;
	}
}

void BezierCurve::mouseReleased() {
	m_anchor0Clicked = false;
	m_anchor1Clicked = false;
	m_point0Clicked = false;
	m_point1Clicked = false;
	m_point2Clicked = false;
}

void BezierCurve::mouseDragged(int x, int y) {
	if (m_anchor0Clicked) {
		m_anchor0 = glm::vec2(x, y);
		return;
	}
	if (m_anchor1Clicked) {
		m_anchor1 = glm::vec2(x, y);
		return;
	}
	if (m_point0Clicked) {
		m_point0 = glm::vec2(x, y);
		return;
	}
	if (m_point1Clicked) {
		m_point1 = glm::vec2(x, y);
		return;
	}
	if (m_point2Clicked) {
		m_point2 = glm::vec2(x, y);
		return;
	}
}

void BezierCurve::draw(const Window& window, const Camera& camera) {
	ofSetColor(255, 255, 255);
	ofDrawCircle(m_anchor0.x, m_anchor0.y, m_pointRadius);
	ofDrawCircle(m_anchor1.x, m_anchor1.y, m_pointRadius);
	ofDrawCircle(m_point0.x, m_point0.y, m_pointRadius);
	ofDrawCircle(m_point1.x, m_point1.y, m_pointRadius);
	ofDrawCircle(m_point2.x, m_point2.y, m_pointRadius);

	m_polyline.draw();

}

BezierCurve::~BezierCurve() {

}