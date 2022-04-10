#pragma once
#include "ofxDatGui.h"
#include "../Domain/Window.h"
#include "Themes.h"
#include "../Helper/Log.h"
#include "../Tools/AnimationSaver.h"

class SaveScreen {
public:
	SaveScreen(AnimationSaver* animationSaver, Window* window);
	~SaveScreen();
	void draw(const Window& window);
	void update();

	void showSaveScreen() { m_showSaveScreen = true; }
private:
	bool m_showSaveScreen = false;
	AnimationSaver* m_animationSaver;
	Window* m_window;

	int m_sizeX = 300;
	int m_sizeY = 170;
	int m_buttonWidth = 100;
	int m_paddingX = 5;

	int m_nbOfFramesToSave = 1;
	int m_fps = 1;

	ofTrueTypeFont m_font;
	ofxDatGuiSlider* m_nbFramesToSaveSlider;
	ofxDatGuiSlider* m_fpsSlider;
	ofxDatGuiButton* m_saveButton;
	ofxDatGuiButton* m_cancelButton;

	void onSaveEvent(ofxDatGuiButtonEvent e);
	void onCancelEvent(ofxDatGuiButtonEvent e);

	void nbOfFramesToSaveChanged(ofxDatGuiSliderEvent e);
	void fpsChanged(ofxDatGuiSliderEvent e);
};
