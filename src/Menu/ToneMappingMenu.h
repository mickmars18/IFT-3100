#pragma once
#include <ofxDatGuiGroups.h>
#include "Themes.h"
#include "../Domain/Object.h"

class ToneMappingMenu {
public:
	ToneMappingMenu();
	~ToneMappingMenu();
	void setup(int posX, int posY, int width, int height, int padding);
	void update();
	void draw();

	void setActiveObjects(const std::vector<Object*>& object);
private:
	ofxDatGuiSlider* m_gammaSlider;
	ofxDatGuiSlider* m_exposureSlider;
	ofxDatGuiToggle* m_toggle;

	void onToggle(ofxDatGuiButtonEvent e);
	void onGammaChange(ofxDatGuiSliderEvent e);
	void onExposureChange(ofxDatGuiSliderEvent e);

	std::vector<Object*> m_activeObject;
};
