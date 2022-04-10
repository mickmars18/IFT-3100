#include "NoiseTextureMenu.h"

NoiseTextureMenu::NoiseTextureMenu() {
	m_font.load(Themes::getFontName(), 12);

	m_scaleSlider = new ofxDatGuiSlider("Scale", 1.0f, 200.0f, 100.0f);
	m_scaleSlider->setTheme(Themes::getThemeSlider());
	m_scaleSlider->onSliderEvent(this, &NoiseTextureMenu::onScaleSliderEvent);

	m_sizeSlider = new ofxDatGuiSlider("Texture Size", 10.0f, 2000.0f, 1000.0f);
	m_sizeSlider->setTheme(Themes::getThemeSlider());
	m_sizeSlider->onSliderEvent(this, &NoiseTextureMenu::onSizeSliderEvent);

	m_woodScaleSlider = new ofxDatGuiSlider("Wood Scale", 0.0f, 200.0f, 0.0f);
	m_woodScaleSlider->setTheme(Themes::getThemeSlider());
	m_woodScaleSlider->onSliderEvent(this, &NoiseTextureMenu::onWoodScaleSliderEvent);

	m_scale = 100.0f;
	m_woodScale = 0.0f;
	m_size = 1000;
}

void NoiseTextureMenu::setup(int width, int posX, int posY, int paddingX, int paddingY) {
	m_scaleSlider->setWidth(width, 0.32f);
	m_sizeSlider->setWidth(width, 0.32f);
	m_woodScaleSlider->setWidth(width, 0.32f);

	m_fontPosition = ofVec2f(posX + 55, posY);
	m_sizeSlider->setPosition(posX, posY + paddingY + 9);
	m_scaleSlider->setPosition(posX, m_sizeSlider->getY() + m_sizeSlider->getHeight() + paddingY);
	m_woodScaleSlider->setPosition(posX, m_scaleSlider->getY() + m_scaleSlider->getHeight() + paddingY);
}

void NoiseTextureMenu::draw() {
	m_font.drawString("Noise texture options", m_fontPosition.x, m_fontPosition.y);
	m_sizeSlider->draw();
	m_scaleSlider->draw();
	m_woodScaleSlider->draw();
}

void NoiseTextureMenu::update() {
	m_sizeSlider->update();
	m_scaleSlider->update();
	m_woodScaleSlider->update();
}

void NoiseTextureMenu::onScaleSliderEvent(ofxDatGuiSliderEvent e) {
	m_scale = e.value;
	m_noiseTexture->setTexture(m_size, m_size, m_scale, m_woodScale);
}

void NoiseTextureMenu::onWoodScaleSliderEvent(ofxDatGuiSliderEvent e) {
	m_woodScale = e.value;
	m_noiseTexture->setTexture(m_size, m_size, m_scale, m_woodScale);
}

void NoiseTextureMenu::onSizeSliderEvent(ofxDatGuiSliderEvent e) {
	m_size = (int)e.value;
	m_sizeSlider->setValue(m_size);
	m_noiseTexture->setTexture(m_size, m_size, m_scale, m_woodScale);
}

NoiseTextureMenu::~NoiseTextureMenu() {
	delete m_scaleSlider;
	delete m_sizeSlider;
	delete m_woodScaleSlider;
}