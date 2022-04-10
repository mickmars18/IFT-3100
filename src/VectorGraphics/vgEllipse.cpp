#include "vgEllipse.h"

vgEllipse::vgEllipse(int x, int y, ofPoint radius, const ofColor& color, int lineWidth, const ofColor& lineColor) :
	m_radius(radius), m_color(color), m_lineWidth(lineWidth), m_lineColor(lineColor)
{
	setName("Ellipse");
	m_transform.setPosition(x, y, 0);
}

std::string vgEllipse::getClassName() {
	return "vgEllipse";
}

void vgEllipse::update() {

}

void vgEllipse::changeColor(const ofColor& color) {
	m_color = color;
}

void vgEllipse::draw(const Window& window, const Camera& camera) {
	ofSetCircleResolution(48);
	ofSetColor(m_lineColor);
	ofDrawEllipse(m_transform.getPosition().x, m_transform.getPosition().y, m_radius.x, m_radius.y);

	ofSetColor(m_color);
	ofDrawEllipse(m_transform.getPosition().x, m_transform.getPosition().y, m_radius.x - m_lineWidth * 2, m_radius.y - m_lineWidth * 2);
	ofSetColor(255);
}