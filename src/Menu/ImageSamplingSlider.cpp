#include "ImageSamplingSlider.h"

ImageSamplingSlider::ImageSamplingSlider() {
	m_slider = new ofxDatGuiSlider("Sampling", 0.0f, 1.0f);
	m_slider->onSliderEvent(this, &ImageSamplingSlider::onSliderEvent);
}

void ImageSamplingSlider::setup(int width, int posX, int posY, int paddingX, int paddingY) {
	m_slider->setTheme(Themes::getThemeSlider());
	m_slider->setWidth(width - 2 * paddingX, 0.28f);
	m_slider->setPosition(posX, posY + 2 * paddingY);
}

void ImageSamplingSlider::setObject(ImageSampling* imageSampling) {
	m_imageSampling = imageSampling;
}

void ImageSamplingSlider::onSliderEvent(ofxDatGuiSliderEvent e)
{
	m_imageSampling->recalculateImage(e.value);
}

void ImageSamplingSlider::update()
{
    m_slider->update();
}

void ImageSamplingSlider::draw()
{
    m_slider->draw();
}