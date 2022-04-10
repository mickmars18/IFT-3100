#include "ImageSampling.h"

ImageSampling::ImageSampling(const std::string& image1, const std::string& image2)
{
	ofDisableArbTex();
	m_shader.load("shaders/image_330_vs.glsl", "shaders/image_330_fs.glsl");

	m_image1 = new ofImage(image1);
	m_shader.setUniformTexture("image1", m_image1->getTexture(), 0);

	m_image2 = new ofImage(image2);
	m_shader.setUniformTexture("image2", m_image2->getTexture(), 1);

	resizeImages();
	m_imageToDraw = new Image(image1);
	recalculateImage(m_factor);

	m_name = "Image Sampling";

	m_transform.setOrigin(m_image1->getWidth() / 2, m_image1->getHeight() / 2, 0.0f);
	m_transform.setPosition(0.0f, m_image1->getHeight() / 2, 0.0f);
}

void ImageSampling::resizeImages() {
	int minWidth = min(m_image1->getWidth(), m_image2->getWidth());
	int minHeight = min(m_image1->getHeight(), m_image2->getHeight());
	m_image1->resize(minWidth, minHeight);
	m_image2->resize(minWidth, minHeight);
	m_width = minWidth;
	m_height = minHeight;
}

void ImageSampling::update() {
	m_image1->update();
	m_image2->update();
	m_imageToDraw->update();

	m_imageToDraw->setTransform(getTransform());
}

void ImageSampling::draw(const Window& window, const Camera& camera) {
	m_imageToDraw->draw(window, camera);
}

void ImageSampling::recalculateImage(float factor) {
	m_factor = factor;

	ofPixels newPixels;
	ofPixels pixels1 = m_image1->getPixels();
	ofPixels pixels2 = m_image2->getPixels();
	newPixels.allocate(m_width, m_height, ofImageType::OF_IMAGE_COLOR);
	for (size_t i = 0; i < m_width * 3; i += 3)
	{
		for (size_t j = 0; j < m_height * 3; j += 3)
		{
			int index = i * m_width + j;
			float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			if (r < factor) {
				newPixels[index] = pixels1[index];
				newPixels[index + 1] = pixels1[index + 1];
				newPixels[index + 2] = pixels1[index + 2];
			}
			else {
				newPixels[index] = pixels2[index];
				newPixels[index + 1] = pixels2[index + 1];
				newPixels[index + 2] = pixels2[index + 2];
			}
		}
	}
	m_imageToDraw->setImage(newPixels);
}

ImageSampling::~ImageSampling() {
	delete m_image1;
	delete m_image2;
}