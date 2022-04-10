#pragma once
#include "ofxDatGui.h"
#include "Themes.h"
#include "../Domain/Object.h"
#include "../VectorGraphics/VectorGraphics.h"

class RandomizeButton {
public:
	RandomizeButton();
	~RandomizeButton();
	void setup(int posX, int posY, int width);
	void setPosY(int posY);
	void update();
	void draw();
	void onButtonEvent(ofxDatGuiButtonEvent e);
	void setObjects(const std::vector<Object*>& activeObjects);
private:
	ofxDatGuiButton* m_button;
	std::vector<Object*> m_activeObjects;
	int m_posX;
	int m_posY;
};
