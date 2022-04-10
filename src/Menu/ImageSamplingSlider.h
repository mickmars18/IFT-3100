#pragma once

#include "ofxDatGui.h"
#include "../Image/ImageSampling.h"
#include "Themes.h"

class ImageSamplingSlider {
public:
	ImageSamplingSlider();
	void setup(int width, int posX, int posY, int paddingX, int paddingY);

	void update();
	void draw();

	void onSliderEvent(ofxDatGuiSliderEvent e);

	void setObject(ImageSampling* imageSampling);

private:
	ofxDatGuiSlider* m_slider;
	ImageSampling* m_imageSampling;
};
