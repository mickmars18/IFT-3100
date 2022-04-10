#include "ToneMappingMenu.h"

ToneMappingMenu::ToneMappingMenu() {
	m_gammaSlider = new ofxDatGuiSlider("Gamma", 0.0f, 5.0f);
	m_exposureSlider = new ofxDatGuiSlider("Exposure", 0.0f, 5.0f);
	m_toggle = new ofxDatGuiToggle("Aces filmic", true);
}

void ToneMappingMenu::setup(int posX, int posY, int width, int height, int padding) {
	m_gammaSlider->setTheme(Themes::getThemeSlider());
	m_gammaSlider->setWidth(width, 0.26f);
	m_gammaSlider->setPosition(posX, posY);

	m_exposureSlider->setTheme(Themes::getThemeSlider());
	m_exposureSlider->setWidth(width, 0.26f);
	m_exposureSlider->setPosition(posX, m_gammaSlider->getY() + m_gammaSlider->getHeight() + padding);

	m_toggle->setTheme(Themes::getThemeSlider());
	m_toggle->setPosition(posX, m_exposureSlider->getY() + m_exposureSlider->getHeight() + padding);
	m_toggle->setWidth(120.0f);

	m_toggle->onButtonEvent(this, &ToneMappingMenu::onToggle);
	m_gammaSlider->onSliderEvent(this, &ToneMappingMenu::onGammaChange);
	m_exposureSlider->onSliderEvent(this, &ToneMappingMenu::onExposureChange);
}

void ToneMappingMenu::setActiveObjects(const std::vector<Object*>& object) {
	m_activeObject = object;

	m_gammaSlider->setValue(2.2f);
	m_exposureSlider->setValue(1.0f);
	m_toggle->setChecked(true);

	for (size_t i = 0; i < m_activeObject.size(); i++) {
		m_activeObject[i]->setToggleToneMapping(m_toggle->getChecked());
		m_activeObject[i]->setGammaToneMapping(m_gammaSlider->getValue());
		m_activeObject[i]->setExposureToneMapping(m_exposureSlider->getValue());
	}
}

void ToneMappingMenu::onToggle(ofxDatGuiButtonEvent e) {
	if (m_toggle->getChecked())
		m_toggle->setLabel("Aces filmic");
	else
		m_toggle->setLabel("Reinhard");

	for (size_t i = 0; i < m_activeObject.size(); i++) {
		m_activeObject[i]->setToggleToneMapping(m_toggle->getChecked());
	}
}

void ToneMappingMenu::onGammaChange(ofxDatGuiSliderEvent e) {
	for (size_t i = 0; i < m_activeObject.size(); i++) {
		m_activeObject[i]->setGammaToneMapping(e.value);
	}
}

void ToneMappingMenu::onExposureChange(ofxDatGuiSliderEvent e) {
	for (size_t i = 0; i < m_activeObject.size(); i++) {
		m_activeObject[i]->setExposureToneMapping(e.value);
	}
}

void ToneMappingMenu::update() {
	m_gammaSlider->update();
	m_exposureSlider->update();
	m_toggle->update();
}

void ToneMappingMenu::draw() {
	m_gammaSlider->draw();
	m_exposureSlider->draw();
	m_toggle->draw();
}

ToneMappingMenu::~ToneMappingMenu() {
	delete m_gammaSlider;
	delete m_exposureSlider;
	delete m_toggle;
}