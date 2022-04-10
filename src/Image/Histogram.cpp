#include "Histogram.h"

Histogram::Histogram() {
	m_histogramCalculated = false;
	for (size_t i = 0; i < 256; i++) {
		redCount[i] = 0;
		greenCount[i] = 0;
		blueCount[i] = 0;
	}
}

void Histogram::update() {

}

void Histogram::draw(const Window& window, const ofImage* image, bool newColor) {
	int width = window.getWidth() / 2;
	int height = window.getHeight() / 2;
	int x = window.getWidth() / 4;
	int y = window.getHeight() / 4;

	ofRectangle background(x, y, width, height);
	ofSetColor(35, 35, 35, 255);
	ofDrawRectangle(background);

	if (!m_histogramCalculated || newColor)
		calculateHistogram(window, x, y, width, height, image);

	ofEnableBlendMode(OF_BLENDMODE_ADD);
	ofSetColor(255, 0, 0);
	for (size_t i = 0; i < 256; i++) {
		ofDrawRectangle(x + redRectangle[i].x + m_padding, y + redRectangle[i].y - m_padding, 0, redRectangle[i].width, redRectangle[i].height);
	}
	ofSetColor(0, 255, 0);
	for (size_t i = 0; i < 256; i++) {
		ofDrawRectangle(x + greenRectangle[i].x + m_padding, y + greenRectangle[i].y - m_padding, 0, greenRectangle[i].width, greenRectangle[i].height);
	}
	ofSetColor(0, 0, 255);
	for (size_t i = 0; i < 256; i++) {
		ofDrawRectangle(x + blueRectangle[i].x + m_padding, y + blueRectangle[i].y - m_padding, 0, blueRectangle[i].width, blueRectangle[i].height);
	}
	ofEnableBlendMode(OF_BLENDMODE_DISABLED);

	ofSetColor(0, 0, 0);
	float lineWidth = 3.0f;
	ofSetLineWidth(lineWidth);
	glm::vec2 point1(x + m_padding, y + height - m_padding);
	glm::vec2 point2(x + m_padding, y + m_padding / 2.0f);
	glm::vec2 point3(x + width - m_padding / 2.0f, y + height - m_padding);
	ofDrawLine(point1, point2);
	ofDrawLine(point1, point3);

	ofSetColor(255, 255, 255, 255);

	float textWidth1 = 125.0f;
	ofDrawBitmapString("Intensity value", (point1.x + point3.x - textWidth1) / 2, point1.y + m_padding / 2);

	float margin = 5.0f;
	ofDrawBitmapString("Count", point1.x - m_padding + margin, (point1.y + point2.y) / 2);
}

void Histogram::calculateHistogram(const Window& window, int x, int y, int width, int height, const ofImage* image) {
	m_histogramCalculated = true;
	for (size_t i = 0; i < 256; i++) {
		redCount[i] = 0;
		greenCount[i] = 0;
		blueCount[i] = 0;
	}
	m_maxCount = 0;

	ofPixels pixels = image->getPixels();
	int size = pixels.size();
	int numberOfChannels = pixels.getBitsPerPixel() / 8;
	for (int i = 0; i < pixels.size(); i+=3) {
		redCount[pixels[i]]++;
		greenCount[pixels[i + 1]]++;
		blueCount[pixels[i + 2]]++;
		i += numberOfChannels - 3;
	}

	for (size_t i = 0; i < 256; i++) {
		if (redCount[i] > m_maxCount)
			m_maxCount = redCount[i];
		if (greenCount[i] > m_maxCount)
			m_maxCount = greenCount[i];
		if (blueCount[i] > m_maxCount)
			m_maxCount = blueCount[i];
	}

	float rectWidth = ((float)width - (float)m_padding * 2.0f) / 256.0f;

	for (size_t i = 0; i < 256; i++) {
		float count = redCount[i];
		count = count / m_maxCount * (height - m_padding * 2);
		redRectangle[i].set(rectWidth * i, height - count, width / 256, count);
	}

	for (size_t i = 0; i < 256; i++) {
		float count = greenCount[i];
		count = count / m_maxCount * (height - m_padding * 2);
		greenRectangle[i].set(rectWidth * i, height - count, width / 256, count);
	}

	for (size_t i = 0; i < 256; i++) {
		float count = blueCount[i];
		count = count / m_maxCount * (height - m_padding * 2);
		blueRectangle[i].set(rectWidth * i, height - count, width / 256, count);
	}
}