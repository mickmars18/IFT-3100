#include "vgCircle.h"

vgCircle::vgCircle(int x, int y, int radius, const ofColor& color, int lineWidth, const ofColor& lineColor) :
	m_radius(radius), m_color(color), m_lineWidth(lineWidth), m_lineColor(lineColor)
{
	setName("Circle");
	m_transform.setPosition(x, y, 0);
}

std::string vgCircle::getClassName() {
	return "vgCircle";
}

void vgCircle::update() {

}

void vgCircle::changeColor(const ofColor& color) {
	m_color = color;
}

void vgCircle::draw(const Window& window, const Camera& camera) {

	ofSetCircleResolution(48);

	ofSetColor(m_lineColor);
	ofDrawEllipse(m_transform.getPosition().x, m_transform.getPosition().y, m_radius, m_radius);

	ofSetColor(m_color);
	ofDrawEllipse(m_transform.getPosition().x, m_transform.getPosition().y, m_radius - m_lineWidth * 2, m_radius - m_lineWidth * 2);
	ofSetColor(255);
}