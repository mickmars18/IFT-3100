#pragma once
#include "of3dUtils.h"
#include "glm/glm.hpp"
#include <graphics/ofGraphics.h>
#include <app/ofAppRunner.h>
#include "../Domain/Window.h"

class AxisGizmo {
public:
	void draw(int menuWidth) {
		ofPushMatrix();
		ofTranslate(glm::vec2(menuWidth + m_padding, ofGetWindowHeight() - m_padding));
		ofRotateXDeg(180.0f);
		ofDrawRotationAxes(65.0f, 0.0f, 0.0f);
		ofPopMatrix();
	}
private:
	float m_padding = 15.0f;
};
