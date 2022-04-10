#pragma once
#include "ofxDatGui.h"
#include "Themes.h"
#include "../Image/NoiseTexture.h"

class NoiseTextureMenu {
public:
	NoiseTextureMenu();
	~NoiseTextureMenu();
	void setup(int width, int posX, int posY, int paddingX, int paddingY);

	void draw();
	void update();

	void setTexture(NoiseTexture* noiseTexture) { m_noiseTexture = noiseTexture; }
private:
	ofTrueTypeFont m_font;
	ofVec2f m_fontPosition;
	ofxDatGuiSlider* m_scaleSlider;
	ofxDatGuiSlider* m_woodScaleSlider;
	ofxDatGuiSlider* m_sizeSlider;

	NoiseTexture* m_noiseTexture = nullptr;

	double m_scale;
	double m_woodScale;
	int m_size;

	void onScaleSliderEvent(ofxDatGuiSliderEvent e);
	void onWoodScaleSliderEvent(ofxDatGuiSliderEvent e);
	void onSizeSliderEvent(ofxDatGuiSliderEvent e);
};
