#include "Image.h"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

Image::Image(const std::string& filename) {
	ofDisableArbTex();
	m_shader.load("shaders/image_330_vs.glsl", "shaders/image_330_fs.glsl");

	m_image = new ofImage(filename);
	m_imageColorized = new ofImage(filename);
	m_newColor = true;
	m_color = ofColor(255, 255, 255);

	m_transform.setOrigin(m_image->getWidth() / 2, m_image->getHeight() / 2, 0.0f);
	m_transform.setPosition(0.0f, 0.0f, 0.0f);

	m_name = getFilenameFormatted(filename);
	m_histogram = new Histogram();
	m_showHistogram = false;

	m_shader.setUniformTexture("image", m_image->getTexture(), 0);
}

void Image::update() {
	m_image->update();
}

std::string Image::getFilenameFormatted(std::string filename) const {
	std::stack<char> resultInverse;
	bool dotFound = false;
	for (std::string::size_type i = filename.size() - 1; i > 0; --i) {
		if (filename[i] == '/' || filename[i] == '\\')
			break;
		if (dotFound) {
			resultInverse.push(filename[i]);
		}
		if (filename[i] == '.')
			dotFound = true;
	}

	std::string result;
	while (!resultInverse.empty()) {
		result.push_back(resultInverse.top());
		resultInverse.pop();
	}
	return result;
}

void Image::draw(const Window& window, const Camera& camera) {
	if (!m_showHistogram) {
		ofEnableDepthTest();
		m_shader.begin();
		m_shader.setUniform3f("color",
			glm::vec3((float)m_color.r / 255.0f, (float)m_color.g / 255.0f, (float)m_color.b / 255.0f));

		m_transform.addRotationX(180.0f);
		m_shader.setUniformMatrix4f("modelview", camera.getViewMatrix() * getModel());
		m_shader.setUniformMatrix4f("projection", camera.getProjection());
		m_image->draw(0, 0);
		m_transform.addRotationX(-180.0f);
		m_shader.end();
		ofDisableDepthTest();
	}
	else {
		if (m_newColor) {
			recalculateColorizedImage();
		}
		m_histogram->draw(window, m_imageColorized, m_newColor);
		m_newColor = false;
	}
}

void Image::keyReleased(int key) {
	if (key == 104)
		m_showHistogram = !m_showHistogram;
}

void Image::changeColor(const ofColor& color) {
	m_newColor = true;
	m_color = color;
}

void Image::recalculateColorizedImage() {
	std::cout << "Recalculating" << std::endl;

	float red = m_color.r / 255.0f;
	float green = m_color.g / 255.0f;
	float blue = m_color.b / 255.0f;

	ofPixels newPixels = m_image->getPixels();
	int size = newPixels.size();
	int numberOfChannels = newPixels.getBitsPerPixel() / 8;
	for (int i = 0; i < newPixels.size(); i += 3) {
		newPixels[i] *= red;
		newPixels[i + 1] *= green;
		newPixels[i + 2] *= blue;
		i += numberOfChannels - 3;
	}

	delete m_imageColorized;
	m_imageColorized = new ofImage(newPixels);
}

void Image::setImage(const ofPixels& pixels) {
	delete m_image;
	m_image = new ofImage(pixels);
}

ofColor Image::getColor() const {
	return m_color;
}

Image::~Image() {
	delete m_histogram;
	delete m_image;
	delete m_imageColorized;
}