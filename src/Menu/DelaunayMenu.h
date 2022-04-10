#pragma once
#include "ofxDatGui.h"
#include "../Domain/Object.h"
#include "Themes.h"
#include "../Topology/Delaunay.h"

class DelaunayMenu {
public:
	DelaunayMenu();
	~DelaunayMenu();
	void setup(int width, int posX, int posY, int paddingX, int paddingY);
	void update();
	void draw();
	void setObjects(std::vector<Object*> objects);
	void generate();
	void onNbPointsSliderEvent(ofxDatGuiSliderEvent e);
	void onGenerateButtonEvent(ofxDatGuiButtonEvent e);
	void onColorButtonEvent(ofxDatGuiButtonEvent e);
private:
	ofxDatGuiLabel* m_label;
	ofxDatGuiSlider* m_nbPointsSlider;
	ofxDatGuiButton* m_colorButton;
	ofxDatGuiButton* m_generateButton;
	std::vector<Object*> m_objects;

	int m_defaultValue = 100;
	int m_nbPoints;
};
