#include "SaveScreen.h"

SaveScreen::SaveScreen(AnimationSaver* animationSaver, Window* window) {
	m_animationSaver = animationSaver;
	m_window = window;
	m_font.load(Themes::getFontName(), 16);

	m_nbFramesToSaveSlider = new ofxDatGuiSlider("Nb of frames", 1.0f, 360.0f, m_nbOfFramesToSave);
	m_nbFramesToSaveSlider->onSliderEvent(this, &SaveScreen::nbOfFramesToSaveChanged);
	m_nbFramesToSaveSlider->setTheme(Themes::getLabelTheme());
	m_nbFramesToSaveSlider->setWidth(m_sizeX - 2 * m_paddingX, 0.35f);

	m_fpsSlider = new ofxDatGuiSlider("FPS", 1.0f, 5.0f, m_fps);
	m_fpsSlider->onSliderEvent(this, &SaveScreen::fpsChanged);
	m_fpsSlider->setTheme(Themes::getLabelTheme());
	m_fpsSlider->setWidth(m_sizeX - 2 * m_paddingX, 0.35f);

	m_saveButton = new ofxDatGuiButton("Save");
	m_saveButton->onButtonEvent(this, &SaveScreen::onSaveEvent);
	m_saveButton->setTheme(Themes::getLabelTheme());
	m_saveButton->setStripeColor(ofColor(40, 180, 40));
	m_saveButton->setWidth(m_buttonWidth);

	m_cancelButton = new ofxDatGuiButton("Cancel");
	m_cancelButton->onButtonEvent(this, &SaveScreen::onCancelEvent);
	m_cancelButton->setTheme(Themes::getLabelTheme());
	m_cancelButton->setStripeColor(ofColor(180, 40, 40));
	m_cancelButton->setWidth(m_buttonWidth);
}

void SaveScreen::draw(const Window& window) {
	if (!m_showSaveScreen)
		return;

	ofEnableBlendMode(OF_BLENDMODE_DISABLED);
	ofSetColor(30, 30, 30);

	int posX = window.getX() + (window.getWidth() - m_sizeX) / 2;
	int posY = window.getY() + (window.getHeight() - m_sizeY) / 2;
	ofDrawRectangle(ofRectangle(posX, posY, m_sizeX, m_sizeY));
	ofSetColor(240, 240, 240);

	m_font.drawString("Saving Scene Settings", posX + 35, posY + 30);

	ofSetLineWidth(2.0f);
	ofDrawLine(posX, posY, posX + m_sizeX, posY);
	ofDrawLine(posX + m_sizeX, posY, posX + m_sizeX, posY + m_sizeY);
	ofDrawLine(posX + m_sizeX, posY + m_sizeY, posX, posY + m_sizeY);
	ofDrawLine(posX, posY + m_sizeY, posX, posY);


	m_nbFramesToSaveSlider->setPosition(posX + m_paddingX, posY + 50);
	m_nbFramesToSaveSlider->draw();

	m_fpsSlider->setPosition(posX + m_paddingX, m_nbFramesToSaveSlider->getY() + m_nbFramesToSaveSlider->getHeight() + 6);
	m_fpsSlider->draw();

	int spaceBetweenButtons = 20;
	posX += (m_sizeX - 2 * m_buttonWidth - spaceBetweenButtons) / 2;

	m_saveButton->setPosition(posX, m_fpsSlider->getY() + m_fpsSlider->getHeight() + 15);
	m_saveButton->draw();

	m_cancelButton->setPosition(m_saveButton->getX() + m_saveButton->getWidth() + spaceBetweenButtons, m_saveButton->getY());
	m_cancelButton->draw();

	ofSetColor(255, 255, 255);
}

void SaveScreen::update() {
	m_nbFramesToSaveSlider->update();
	m_fpsSlider->update();
	m_saveButton->update();
	m_cancelButton->update();
}

void SaveScreen::nbOfFramesToSaveChanged(ofxDatGuiSliderEvent e) {
	int newValue = round(e.value);
	m_nbOfFramesToSave = newValue;
	m_nbFramesToSaveSlider->setValue(newValue);
}

void SaveScreen::fpsChanged(ofxDatGuiSliderEvent e) {
	int newValue = round(e.value);
	m_fps = newValue;
	m_fpsSlider->setValue(newValue);
}

void SaveScreen::onSaveEvent(ofxDatGuiButtonEvent e) {
	m_showSaveScreen = false;
	m_animationSaver->saveAnimation(m_nbOfFramesToSave, m_fps, *m_window);
}

void SaveScreen::onCancelEvent(ofxDatGuiButtonEvent e) {
	m_showSaveScreen = false;
}

SaveScreen::~SaveScreen() {
	delete m_nbFramesToSaveSlider;
	delete m_fpsSlider;
	delete m_saveButton;
	delete m_cancelButton;
}