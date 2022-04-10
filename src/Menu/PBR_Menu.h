#pragma once
#include "ofxDatGui.h"
#include "Themes.h"
#include "../Domain/Object.h"
#include "../PBR/PBR_Model.h"

class PBR_Menu {
public:
	PBR_Menu();
	~PBR_Menu();
	void setup(int posX, int posY, int width, int padding);
	void setObjects(std::vector<Object*> objects);
	void draw();
	void update();
private:
	std::vector<PBR_Model*> m_objects;

	ofTrueTypeFont m_font;
	ofVec2f m_fontPosition;

	ofxDatGuiSlider* m_brightnessSlider;
	ofxDatGuiSlider* m_metallicSlider;
	ofxDatGuiSlider* m_roughnessSlider;
	ofxDatGuiSlider* m_occlusionSlider;
	ofxDatGuiSlider* m_fresnelXSlider;
	ofxDatGuiSlider* m_fresnelYSlider;
	ofxDatGuiSlider* m_fresnelZSlider;
	ofxDatGuiSlider* m_exposureSlider;
	ofxDatGuiSlider* m_gammaSlider;

	void onBrightnessSliderEvent(ofxDatGuiSliderEvent e);
	void onMetallicSliderEvent(ofxDatGuiSliderEvent e);
	void onRoughnessSliderEvent(ofxDatGuiSliderEvent e);
	void onOcclusionSliderEvent(ofxDatGuiSliderEvent e);
	void onFresnelXSliderEvent(ofxDatGuiSliderEvent e);
	void onFresnelYSliderEvent(ofxDatGuiSliderEvent e);
	void onFresnelZSliderEvent(ofxDatGuiSliderEvent e);
	void onExposureSliderEvent(ofxDatGuiSliderEvent e);
	void onGammaSliderEvent(ofxDatGuiSliderEvent e);
};
