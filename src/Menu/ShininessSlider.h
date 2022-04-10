#pragma once
#include <ofxDatGui.h>
#include "Themes.h"
#include "../Domain/Object.h"
#include "../Models/Model.h"

class ShininessSlider {
public:
	ShininessSlider();
	~ShininessSlider();
	void setup(int posX, int posY, int width);
	void setObject(const std::vector<Object*>& objects);

	void draw();
	void update();

	void onChange(ofxDatGuiSliderEvent e);

	float transformShininess(float shininess);
	float inverseShininess(float shininess);
private:
	ofTrueTypeFont m_font;
	ofxDatGuiSlider* m_shininessSlider;
	std::vector<Object*> m_objects;
};