#pragma once
#include "ofxDatGui.h"
#include "Themes.h"
#include "../Raytracing/RT_App.h"

class RT_Menu {
public:
	RT_Menu();
	void setup(int posX, int posY, int width, int padding);
	void setRT_App(RT_App* rt_app);
	~RT_Menu();

	void draw();
	void update();
private:
	RT_App* m_RT_App = nullptr;

	ofTrueTypeFont m_font;
	ofTrueTypeFont m_progressionFont;
	int m_titlePosX;
	int m_titlePosY;
	int m_pctPosX;
	int m_pctPosY;

	ofxDatGuiTextInput* m_samplesPerPixelInput;
	ofxDatGuiSlider* m_maxBouncesSlider;
	ofxDatGuiSlider* m_qualitySlider;
	ofxDatGuiButton* m_generateImageButton;

	ofParameter<int> ofMaxBouncesInt;
	ofParameter<int> ofQualityInt;

	void onSamplesPerPixelInputEvent(ofxDatGuiTextInputEvent e);
	void onGenerateEvent(ofxDatGuiButtonEvent e);

	void onMaxBouncesChanged(int& pInt);
	void onQualityChanged(int& pInt);

	void onMaxBouncesSliderEvent(ofxDatGuiSliderEvent e);
	void onQualitySliderEvent(ofxDatGuiSliderEvent e);
};


