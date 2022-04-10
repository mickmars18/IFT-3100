#include "vgSquare.h"

vgSquare::vgSquare(int x, int y, int width, const ofColor& color, int lineWidth, const ofColor& lineColor) :
	m_width(width), m_color(color), m_lineWidth(lineWidth), m_lineColor(lineColor)
{
	setName("Square");
	m_transform.setPosition(x, y, 0);
}

std::string vgSquare::getClassName() {
	return "vgSquare";
}

void vgSquare::update() {

}

void vgSquare::changeColor(const ofColor& color) {
	m_color = color;
}

void vgSquare::draw(const Window& window, const Camera& camera) {
	ofSetColor(m_lineColor);
	ofDrawRectangle(m_transform.getPosition().x, m_transform.getPosition().y, m_width, m_width);

	ofSetColor(m_color);
	ofDrawRectangle(m_transform.getPosition().x + m_lineWidth, m_transform.getPosition().y + m_lineWidth,
		m_width - m_lineWidth * 2, m_width - m_lineWidth * 2);
	ofSetColor(255);
}