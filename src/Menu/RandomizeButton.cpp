#include "RandomizeButton.h"

RandomizeButton::RandomizeButton() {
	m_button = new ofxDatGuiButton("Randomize");
	m_button->setTheme(Themes::getLabelTheme());
	m_button->onButtonEvent(this, &RandomizeButton::onButtonEvent);
}

void RandomizeButton::setup(int posX, int posY, int width) {
	m_button->setPosition(posX, posY);
	m_button->setWidth(width);
	m_posX = posX;
	m_posY = posY;
}

void RandomizeButton::setPosY(int posY) {
	m_button->setPosition(m_posX, posY);
}

void RandomizeButton::update() {
	m_button->update();
}

void RandomizeButton::draw() {
	m_button->draw();
}

void RandomizeButton::onButtonEvent(ofxDatGuiButtonEvent e) {
	for (size_t i = 0; i < m_activeObjects.size(); i++) {
		if (m_activeObjects[i]->getClassName() == "GeometricPattern") {
			dynamic_cast<GeometricPattern*>(m_activeObjects[i])->initForms();
		}
		if (m_activeObjects[i]->getClassName() == "StripedCircles") {
			dynamic_cast<StripedCircle*>(m_activeObjects[i])->reset();
		}
	}
}

void RandomizeButton::setObjects(const std::vector<Object*>& activeObjects) {
	m_activeObjects = activeObjects;
}

RandomizeButton::~RandomizeButton() {
	delete m_button;
}