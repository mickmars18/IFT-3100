#include "StripedCircles.h"

StripedCircle::StripedCircle(int x, int y, int radius, const ofColor& color1, const ofColor& color2, int nbStrips) :
	m_radius(radius), m_color1(color1), m_color2(color2), m_nbStrips(nbStrips)
{
	setName("Striped Circles");
	m_transform.setPosition(x, y, 0);
}

std::string StripedCircle::getClassName() {
	return "StripedCircles";
}

void StripedCircle::update() {

}

void StripedCircle::reset() {
	m_color1 = ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
	m_color2 = ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
	m_nbStrips = (int)ofRandom(20, 40);
}

void StripedCircle::draw(const Window& window, const Camera& camera) {
	ofSetCircleResolution(48);
	ofColor activeColor = m_color1;
	float divFactor = (float)m_nbStrips;
	for (int i = m_nbStrips; i > 0; i--) {
		ofSetColor(activeColor);
		float radius = (float)m_radius * (float)i / divFactor;
		ofDrawEllipse(m_transform.getPosition().x, m_transform.getPosition().y, radius, radius);
		if (activeColor == m_color1)
			activeColor = m_color2;
		else
			activeColor = m_color1;
	}
	ofSetColor(255);
}