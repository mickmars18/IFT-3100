#include "PBR_Menu.h"

PBR_Menu::PBR_Menu() {
	m_font.load(Themes::getFontName(), 12);
	m_metallicSlider = new ofxDatGuiSlider("Metallic", 0.0f, 1.0f, 1.0f);
	m_roughnessSlider = new ofxDatGuiSlider("Roughness", 0.0f, 1.0f, 1.0f);
	m_brightnessSlider = new ofxDatGuiSlider("Brighness", 0.0f, 5.0f, 1.0f);
	m_occlusionSlider = new ofxDatGuiSlider("Occlusion", 0.0f, 5.0f, 1.0f);
	m_fresnelXSlider = new ofxDatGuiSlider("Fresnel X", 0.0f, 1.0f, 0.04f);
	m_fresnelYSlider = new ofxDatGuiSlider("Fresnel Y", 0.0f, 1.0f, 0.04f);
	m_fresnelZSlider = new ofxDatGuiSlider("Fresnel Z", 0.0f, 1.0f, 0.04f);
	m_exposureSlider = new ofxDatGuiSlider("Exposure", 0.0f, 1.0f, 1.0f);
	m_gammaSlider = new ofxDatGuiSlider("Gamma", 0.0f, 5.0f, 2.2f);

	m_metallicSlider->setTheme(Themes::getThemeSlider());
	m_roughnessSlider->setTheme(Themes::getThemeSlider());
	m_brightnessSlider->setTheme(Themes::getThemeSlider());
	m_occlusionSlider->setTheme(Themes::getThemeSlider());
	m_fresnelXSlider->setTheme(Themes::getThemeSlider());
	m_fresnelYSlider->setTheme(Themes::getThemeSlider());
	m_fresnelZSlider->setTheme(Themes::getThemeSlider());
	m_exposureSlider->setTheme(Themes::getThemeSlider());
	m_gammaSlider->setTheme(Themes::getThemeSlider());

	m_metallicSlider->onSliderEvent(this, &PBR_Menu::onMetallicSliderEvent);
	m_roughnessSlider->onSliderEvent(this, &PBR_Menu::onRoughnessSliderEvent);
	m_brightnessSlider->onSliderEvent(this, &PBR_Menu::onBrightnessSliderEvent);
	m_occlusionSlider->onSliderEvent(this, &PBR_Menu::onOcclusionSliderEvent);
	m_fresnelXSlider->onSliderEvent(this, &PBR_Menu::onFresnelXSliderEvent);
	m_fresnelYSlider->onSliderEvent(this, &PBR_Menu::onFresnelYSliderEvent);
	m_fresnelZSlider->onSliderEvent(this, &PBR_Menu::onFresnelZSliderEvent);
	m_exposureSlider->onSliderEvent(this, &PBR_Menu::onExposureSliderEvent);
	m_gammaSlider->onSliderEvent(this, &PBR_Menu::onGammaSliderEvent);
}

void PBR_Menu::setup(int posX, int posY, int width, int padding) {
	m_fontPosition.x = posX + width / 2 - 41;
	m_fontPosition.y = posY;

	int initY = m_fontPosition.y + padding + 10;
	int spaceBetween = m_metallicSlider->getHeight() + padding;
	m_metallicSlider->setPosition(posX, initY);
	m_roughnessSlider->setPosition(posX, initY + spaceBetween);
	m_brightnessSlider->setPosition(posX, initY + 2.0f * spaceBetween);
	m_occlusionSlider->setPosition(posX, initY + 3.0f * spaceBetween);
	m_fresnelXSlider->setPosition(posX, initY + 4.0f * spaceBetween);
	m_fresnelYSlider->setPosition(posX, initY + 5.0f * spaceBetween);
	m_fresnelZSlider->setPosition(posX, initY + 6.0f * spaceBetween);
	m_exposureSlider->setPosition(posX, initY + 7.0f * spaceBetween);
	m_gammaSlider->setPosition(posX, initY + 8.0f * spaceBetween);

	float labelWidth = 0.3f;
	m_metallicSlider->setWidth(width, labelWidth);
	m_roughnessSlider->setWidth(width, labelWidth);
	m_brightnessSlider->setWidth(width, labelWidth);
	m_occlusionSlider->setWidth(width, labelWidth);
	m_fresnelXSlider->setWidth(width, labelWidth);
	m_fresnelYSlider->setWidth(width, labelWidth);
	m_fresnelZSlider->setWidth(width, labelWidth);
	m_exposureSlider->setWidth(width, labelWidth);
	m_gammaSlider->setWidth(width, labelWidth);
}
void PBR_Menu::setObjects(std::vector<Object*> objects) {
	m_objects.clear();
	for (size_t i = 0; i < objects.size(); i++) {
		if (objects[i]->getClassName() == "PBR_Model") {
			PBR_Model* model = dynamic_cast<PBR_Model*>(objects[i]);
			m_objects.push_back(model);
		}
	}
	if (m_objects.size() > 0) {
		m_metallicSlider->setValue(m_objects[0]->getMaterial()->getMetallic());
		m_roughnessSlider->setValue(m_objects[0]->getMaterial()->getRoughness());
		m_brightnessSlider->setValue(m_objects[0]->getMaterial()->getBrightness());
		m_occlusionSlider->setValue(m_objects[0]->getMaterial()->getOcclusion());
		m_fresnelXSlider->setValue(m_objects[0]->getMaterial()->getFresnel_ior().x);
		m_fresnelYSlider->setValue(m_objects[0]->getMaterial()->getFresnel_ior().y);
		m_fresnelZSlider->setValue(m_objects[0]->getMaterial()->getFresnel_ior().z);
		m_exposureSlider->setValue(m_objects[0]->getMaterial()->getExposure());
		m_gammaSlider->setValue(m_objects[0]->getMaterial()->getGamma());
	}
}


void PBR_Menu::onBrightnessSliderEvent(ofxDatGuiSliderEvent e) {
	for (size_t i = 0; i < m_objects.size(); i++) {
		m_objects[i]->getMaterial()->setBrightness(e.value);
	}
}

void PBR_Menu::onMetallicSliderEvent(ofxDatGuiSliderEvent e) {
	for (size_t i = 0; i < m_objects.size(); i++) {
		m_objects[i]->getMaterial()->setMetallic(e.value);
	}
}

void PBR_Menu::onRoughnessSliderEvent(ofxDatGuiSliderEvent e) {
	for (size_t i = 0; i < m_objects.size(); i++) {
		m_objects[i]->getMaterial()->setRoughness(e.value);
	}
}

void PBR_Menu::onOcclusionSliderEvent(ofxDatGuiSliderEvent e) {
	for (size_t i = 0; i < m_objects.size(); i++) {
		m_objects[i]->getMaterial()->setOcclusion(e.value);
	}
}

void PBR_Menu::onFresnelXSliderEvent(ofxDatGuiSliderEvent e) {
	for (size_t i = 0; i < m_objects.size(); i++) {
		m_objects[i]->getMaterial()->setFresnelX_ior(e.value);
	}
}

void PBR_Menu::onFresnelYSliderEvent(ofxDatGuiSliderEvent e) {
	for (size_t i = 0; i < m_objects.size(); i++) {
		m_objects[i]->getMaterial()->setFresnelY_ior(e.value);
	}
}

void PBR_Menu::onFresnelZSliderEvent(ofxDatGuiSliderEvent e) {
	for (size_t i = 0; i < m_objects.size(); i++) {
		m_objects[i]->getMaterial()->setFresnelZ_ior(e.value);
	}
}

void PBR_Menu::onExposureSliderEvent(ofxDatGuiSliderEvent e) {
	for (size_t i = 0; i < m_objects.size(); i++) {
		m_objects[i]->getMaterial()->setExposure(e.value);
	}
}

void PBR_Menu::onGammaSliderEvent(ofxDatGuiSliderEvent e) {
	for (size_t i = 0; i < m_objects.size(); i++) {
		m_objects[i]->getMaterial()->setGamma(e.value);
	}
}

void PBR_Menu::draw() {
	m_font.drawString("PBR options", m_fontPosition.x, m_fontPosition.y);
	m_metallicSlider->draw();
	m_roughnessSlider->draw();
	m_brightnessSlider->draw();
	m_occlusionSlider->draw();
	m_fresnelXSlider->draw();
	m_fresnelYSlider->draw();
	m_fresnelZSlider->draw();
	m_exposureSlider->draw();
	m_gammaSlider->draw();
}

void PBR_Menu::update() {
	m_metallicSlider->update();
	m_roughnessSlider->update();
	m_brightnessSlider->update();
	m_occlusionSlider->update();
	m_fresnelXSlider->update();
	m_fresnelYSlider->update();
	m_fresnelZSlider->update();
	m_exposureSlider->update();
	m_gammaSlider->update();
}

PBR_Menu::~PBR_Menu() {
	delete m_brightnessSlider;
	delete m_metallicSlider;
	delete m_roughnessSlider;
	delete m_occlusionSlider;
	delete m_fresnelXSlider;
	delete m_fresnelYSlider;
	delete m_fresnelZSlider;
	delete m_exposureSlider;
}