#include "RT_Menu.h"

RT_Menu::RT_Menu() {
	m_font.load(Themes::getFontName(), 12);
	m_progressionFont.load(Themes::getFontName(), 10);
	m_samplesPerPixelInput = new ofxDatGuiTextInput("Samples per pixel", "");
	m_samplesPerPixelInput->onTextInputEvent(this, &RT_Menu::onSamplesPerPixelInputEvent);

	m_generateImageButton = new ofxDatGuiButton("Generate Image");
	m_generateImageButton->onButtonEvent(this, &RT_Menu::onGenerateEvent);

	m_maxBouncesSlider = new ofxDatGuiSlider(ofMaxBouncesInt.set("max bounces", 2, 1, 20));
	m_qualitySlider = new ofxDatGuiSlider(ofQualityInt.set("quality", 25, 5, 200));

	m_maxBouncesSlider->onSliderEvent(this, &RT_Menu::onMaxBouncesSliderEvent);
	m_qualitySlider->onSliderEvent(this, &RT_Menu::onQualitySliderEvent);

	ofMaxBouncesInt.addListener(this, &RT_Menu::onMaxBouncesChanged);
	ofQualityInt.addListener(this, &RT_Menu::onQualityChanged);
}

void RT_Menu::setup(int posX, int posY, int width, int padding) {
	m_titlePosX = posX + 70;
	m_titlePosY = posY - 12;
 
	m_samplesPerPixelInput->setTheme(Themes::getLabelTheme());
	m_samplesPerPixelInput->setPosition(posX, posY);
	m_samplesPerPixelInput->setWidth(width, 0.7f);

	int height = m_samplesPerPixelInput->getY() + m_samplesPerPixelInput->getHeight() + padding;
	m_maxBouncesSlider->setTheme(Themes::getThemeSlider());
	m_maxBouncesSlider->setPosition(posX, height);
	m_maxBouncesSlider->setWidth(width, 0.5f);

	height = m_maxBouncesSlider->getY() + m_maxBouncesSlider->getHeight() + padding;
	m_qualitySlider->setTheme(Themes::getThemeSlider());
	m_qualitySlider->setPosition(posX, height);
	m_qualitySlider->setWidth(width, 0.5f);

	height = m_qualitySlider->getY() + m_qualitySlider->getHeight() + padding;
	m_generateImageButton->setTheme(Themes::getLabelTheme());
	m_generateImageButton->setPosition(posX, height);
	m_generateImageButton->setWidth(width);

	m_pctPosX = posX;
	m_pctPosY = m_generateImageButton->getY() + m_generateImageButton->getHeight() + padding + 25;
}

void RT_Menu::setRT_App(RT_App* rt_app) { 
	m_RT_App = rt_app;
	int samplesPerPixels = m_RT_App->getSamplesPerPixels();
	m_samplesPerPixelInput->setText(std::to_string(samplesPerPixels));

	int maxBounces = m_RT_App->getMaxDepth();
	m_maxBouncesSlider->setValue(maxBounces);

	int quality = (int)(m_RT_App->getQuality() * 100.0f);
	m_qualitySlider->setValue(quality);
};

void RT_Menu::draw() {
	m_font.drawString("Ray Tracing options", m_titlePosX, m_titlePosY);

	float progress = m_RT_App->getPct();
	std::string pct;
	if (progress < 1.0f) {
		std::stringstream stream;
		stream << std::fixed << std::setprecision(2) << m_RT_App->getPct() * 100;
		pct = stream.str();
		m_progressionFont.drawString("Progression : " + pct + "%", m_pctPosX, m_pctPosY);
	}
	else {
		m_progressionFont.drawString("Rendering done.", m_pctPosX, m_pctPosY);
	}

	m_samplesPerPixelInput->draw();
	m_generateImageButton->draw();
	m_maxBouncesSlider->draw();
	m_qualitySlider->draw();
}
void RT_Menu::update() {
	if (m_RT_App->isDone()) {
		m_generateImageButton->setLabel("Generate Image");
	}
	m_samplesPerPixelInput->update();
	m_generateImageButton->update();
	m_maxBouncesSlider->update();
	m_qualitySlider->update();
}

void RT_Menu::onSamplesPerPixelInputEvent(ofxDatGuiTextInputEvent e) {
	m_RT_App->setSamplesPerPixels(std::stoi(e.text));
}

void RT_Menu::onMaxBouncesChanged(int& pInt) {
	m_RT_App->setMaxDepth(pInt);
}

void RT_Menu::onQualityChanged(int& pInt) {
	float quality = (float)(pInt);
	m_RT_App->setQuality(quality / 100.0f);
}

void RT_Menu::onMaxBouncesSliderEvent(ofxDatGuiSliderEvent e) {
}

void RT_Menu::onQualitySliderEvent(ofxDatGuiSliderEvent e) {
}

void RT_Menu::onGenerateEvent(ofxDatGuiButtonEvent e) {
	if (m_generateImageButton->getLabel() == "Generate Image") {
		m_RT_App->run();
		m_generateImageButton->setLabel("Cancel");
		return;
	}
	if (m_generateImageButton->getLabel() == "Cancel") {
		m_RT_App->stop();
		m_generateImageButton->setLabel("Generate Image");
		return;
	}

}

RT_Menu::~RT_Menu() {
	delete m_generateImageButton;
	delete m_samplesPerPixelInput;
}