#pragma once

#include "ofxDatGui.h"
#include "Themes.h"
#include "../Domain/Background.h"
#include "../VectorGraphics/VectorGraphicsInitializer.h"

class VectorGraphicsMenu {
public:
	VectorGraphicsMenu();
	~VectorGraphicsMenu();
	void setup(int width, int posX, int posY, int paddingX, int paddingY);
	void resetColorPickersPosition();

	void update();
	void draw();

	void onSliderEvent(ofxDatGuiSliderEvent e);

	void setBackground(Background* background);
	void setVectorGraphicsInitializer(VectorGraphicsInitializer* vectorGraphicsInitializer);

	void onBackgroundColorPickerEvent(ofxDatGuiColorPickerEvent e);
	void onFillColorPickerEvent(ofxDatGuiColorPickerEvent e);
	void onLineColorPickerEvent(ofxDatGuiColorPickerEvent e);
private:
	Background* m_background;
	VectorGraphicsInitializer* m_vectorGraphicsInitializer;

	ofxDatGuiSlider* m_slider;
	ofxDatGuiColorPicker* m_lineColorPicker;
	ofxDatGuiColorPicker* m_fillColorPicker;
	ofxDatGuiColorPicker* m_backgroundColorPicker;

	int m_width;
	int m_posX;
	int m_posY;
	int m_paddingX;
	int m_paddingY;
	int m_colorPickerExpendedHeight = 85;

	int m_lineWidth = 2;
};
