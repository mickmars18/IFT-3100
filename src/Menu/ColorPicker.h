#pragma once
#include "ofxDatGui.h"
#include "../Domain/Object.h"
#include "ColorSpace.h"
#include "Themes.h"

class ColorPicker {
public:
	ColorPicker();
	~ColorPicker();
	void setupColorPicker(int height, int width, int paddingX, int paddingY);
	void setActiveObject(const std::vector<Object*>& object);
	void setColor(ofColor color);
	inline ofColor getActiveColor() const { return m_drawColor; }
	void update();
	void draw();
	int getHeight() const;
	int getBottomCoord() const;
private:
	std::vector<Object*> m_activeObject;

	ofxDatGuiToggle* m_togglePicker;
	ofxDatGuiToggle* m_toggleRGB;
	ofxDatGuiToggle* m_toggleHSB;

	bool m_showPicker;
	bool m_showRGB;
	bool m_showHSB;

	void onTogglePicker(ofxDatGuiButtonEvent e);
	void onToggleRGB(ofxDatGuiButtonEvent e);
	void onToggleHSB(ofxDatGuiButtonEvent e);

	ofxDatGuiLabel* m_label;

	ofxDatGuiColorPicker* m_colorPicker;

	ofxDatGuiSlider* m_sliderRed;
	ofxDatGuiSlider* m_sliderGreen;
	ofxDatGuiSlider* m_sliderBlue;

	ofxDatGuiSlider* m_sliderHue;
	ofxDatGuiSlider* m_sliderSaturation;
	ofxDatGuiSlider* m_sliderBrightness;

	ofxDatGuiTheme m_sliderRedTheme;
	ofxDatGuiTheme m_sliderGreenTheme;
	ofxDatGuiTheme m_sliderBlueTheme;
	void setupThemes();

	void onRedChange(ofxDatGuiSliderEvent e);
	void onGreenChange(ofxDatGuiSliderEvent e);
	void onBlueChange(ofxDatGuiSliderEvent e);
	void onHueChange(ofxDatGuiSliderEvent e);
	void onSaturationChange(ofxDatGuiSliderEvent e);
	void onBrightnessChange(ofxDatGuiSliderEvent e);
	void onColorPickerEvent(ofxDatGuiColorPickerEvent e);

	void setColor();
	void setColorPickerColors();
	void setRGBColors();
	void setHSBColors();

	ofColor m_drawColor;

	int m_posY;
	int m_width;
	int m_paddingX;
	int m_paddingY;
	int m_height;
	void calculateSlidersPositions();
};