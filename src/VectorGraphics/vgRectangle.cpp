#include "vgRectangle.h"

vgRectangle::vgRectangle(int x, int y, ofPoint dimension, const ofColor& color, int lineWidth, const ofColor& lineColor) :
	m_dimension(dimension), m_color(color), m_lineWidth(lineWidth), m_lineColor(lineColor)
{
	setName("Rectangle");
	m_transform.setPosition(x, y, 0);
}

std::string vgRectangle::getClassName() {
	return "vgRectangle";
}

void vgRectangle::update() {

}

void vgRectangle::changeColor(const ofColor& color) {
	m_color = color;
}

void vgRectangle::draw(const Window& window, const Camera& camera) {
	ofSetColor(m_lineColor);
	ofDrawRectangle(m_transform.getPosition().x, m_transform.getPosition().y, m_dimension.x, m_dimension.y);

	ofSetColor(m_color);
	ofDrawRectangle(m_transform.getPosition().x + m_lineWidth, m_transform.getPosition().y + m_lineWidth,
		m_dimension.x - m_lineWidth * 2, m_dimension.y - m_lineWidth * 2);
	ofSetColor(255);
}