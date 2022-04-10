#pragma once
#include <graphics/ofGraphics.h>
#include <app/ofAppRunner.h>

class Background {
public:
	void draw() {
		ofEnableBlendMode(OF_BLENDMODE_DISABLED);
		ofSetColor(m_backgroundColor);
		ofDrawRectangle(ofRectangle(0, 0, ofGetWidth(), ofGetHeight()));
		ofSetColor(255, 255, 255);
	}

	inline void setColor(const ofColor& color) { m_backgroundColor = color; }
	inline ofColor getColor() const { return m_backgroundColor; }
private:
	ofColor m_backgroundColor = ofColor(50);
};
