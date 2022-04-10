#pragma once
#include "ofImage.h"
#include "ofMain.h"
#include "../Domain/Object.h"

class Histogram {
public:
	Histogram();
	void update();
	void draw(const Window& window, const ofImage* image, bool newColor);
	void calculateHistogram(const Window& window, int x, int y, int width, int height, const ofImage* image);
private:
	int redCount[256];
	int blueCount[256];
	int greenCount[256];
	int m_maxCount = 0;

	ofRectangle redRectangle[256];
	ofRectangle greenRectangle[256];
	ofRectangle blueRectangle[256];

	bool m_histogramCalculated;

	int m_padding = 50;
};
