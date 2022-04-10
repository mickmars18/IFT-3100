#include "VectorGraphicsImage.h"

VectorGraphicsImage::VectorGraphicsImage(const std::string& filename) {
	m_name = getFilenameFormatted(filename) + "-vectorGraphics";
	m_image = new ofImage(filename);

}

VectorGraphicsImage::~VectorGraphicsImage() {
	delete m_image;
}

std::string VectorGraphicsImage::getClassName() {
	return "VectorGraphicsImage";
}

void VectorGraphicsImage::update() {

}

void VectorGraphicsImage::draw(const Window& window, const Camera& camera) {
	ofDisableAlphaBlending();

	int circleRadius = 10;

	ofPixels pixels = m_image->getPixels();
	int size = pixels.size();
	int numberOfChannels = pixels.getBitsPerPixel() / 8;
	int x = 0;
	int y = 0;
	for (int i = 0; i < pixels.size(); i += 3) {
		ofColor color(pixels[i], pixels[i + 1], pixels[i + 2], 255);
		i += numberOfChannels - 3;

		x += 1;
		if (x >= pixels.getWidth()) {
			x = 0;
			y += 1;
		}
		
		if (x % circleRadius == 0 && y % circleRadius == 0) {
			ofSetColor(color);
			float radius = (float)circleRadius / ofRandom(2, 4);
			ofDrawCircle(x, y, 0, radius);
		}
	}
}