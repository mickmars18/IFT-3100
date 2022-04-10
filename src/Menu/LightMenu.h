#pragma once
#include <ofxDatGui.h>
#include "Themes.h"
#include "../Domain/Object.h"
#include "../Models/Model.h"

class LightMenu {
public:
	LightMenu();
	~LightMenu();
	void setup(int posX, int posY, int width, int padding);
	void setLightController(LightsController* lightController);

	void setObject(const std::vector<Object*>& objects);

	void draw();
	void update();

	void onIntensityChange(ofxDatGuiSliderEvent e);
	void onDiffusePickerEvent(ofxDatGuiColorPickerEvent e);
	void onSpecularPickerEvent(ofxDatGuiColorPickerEvent e);
private:
	void onDropdownEvent(ofxDatGuiDropdownEvent e);

	ofTrueTypeFont m_font;
	ofxDatGuiDropdown* m_lightModeDropdown;

	ofxDatGuiSlider* m_intensitySlider;

	ofxDatGuiColorPicker* m_diffusePicker;
	ofxDatGuiColorPicker* m_specularPicker;

	std::vector<Object*> m_objects;

	LightsController* m_lightController = nullptr;

	int m_padding = 0;
};
