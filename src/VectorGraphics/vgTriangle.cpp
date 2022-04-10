#include "vgTriangle.h"

vgTriangle::vgTriangle(int x, int y, ofPoint dimension, const ofColor& color, int lineWidth, const ofColor& lineColor) :
	m_dimension(dimension), m_color(color), m_lineWidth(lineWidth), m_lineColor(lineColor)
{
	setName("Triangle");
	m_transform.setPosition(x, y, 0);
}

std::string vgTriangle::getClassName() {
	return "vgTriangle";
}

void vgTriangle::update() {

}

void vgTriangle::changeColor(const ofColor& color) {
	m_color = color;
}

void vgTriangle::draw(const Window& window, const Camera& camera) {

	if (m_dimension.x == 0 || m_dimension.y == 0)
		return;
	
	int posX = m_transform.getPosition().x;
	int posY = m_transform.getPosition().y;

	ofVec2f point1 = ofVec2f(posX, posY);
	ofVec2f point2 = ofVec2f(posX + m_dimension.x, posY + m_dimension.y);
	ofVec2f point3 = ofVec2f(posX - m_dimension.x, posY + m_dimension.y);

	ofSetColor(m_lineColor);
	ofDrawTriangle(point1, point2, point3);

	float hypothenuse = sqrt(m_dimension.x * m_dimension.x + m_dimension.y * m_dimension.y);
	float factor = (hypothenuse - m_lineWidth * 4) / hypothenuse;
	if (factor > 0) {
		ofVec2f newpoint1 = point1 * (1.0f + 2.0f * factor) / 3.0f + point2 * (1.0f - factor) / 3.0f + point3 * (1.0f - factor) / 3.0f;
		ofVec2f newpoint2 = point1 * (1.0f - factor) / 3.0f + point2 * (1.0f + 2.0f * factor) / 3.0f + point3 * (1.0f - factor) / 3.0f;
		ofVec2f newpoint3 = point1 * (1.0f - factor) / 3.0f + point2 * (1.0f - factor) / 3.0f + point3 * (1.0f + 2.0f * factor) / 3.0f;
		ofSetColor(m_color);
		ofDrawTriangle(newpoint1, newpoint2, newpoint3);
	}
	ofSetColor(255);
}