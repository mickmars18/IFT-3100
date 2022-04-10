#pragma once
#include "ofxDatGui.h"
#include "../Models/Icosphere.h"
#include "Themes.h"

class IcosphereMenu {
public:
	IcosphereMenu();
	~IcosphereMenu();
	void setup(int width, int posX, int posY, int paddingX, int paddingY);
	void update();
	void draw();
	void setActiveObject(std::vector<Object*> objects);
	void onPlusButtonEvent(ofxDatGuiButtonEvent e);
	void onMinusButtonEvent(ofxDatGuiButtonEvent e);
private:
	ofxDatGuiLabel* m_label;
	ofxDatGuiButton* m_plusButton;
	ofxDatGuiButton* m_minusButton;

	std::vector<Icosphere*> m_icospheres;
};
