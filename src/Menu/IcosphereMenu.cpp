#include "IcosphereMenu.h"

IcosphereMenu::IcosphereMenu() {
	m_label = new ofxDatGuiLabel("Number of subdivisions");
	m_plusButton = new ofxDatGuiButton("Increase");
	m_minusButton = new ofxDatGuiButton("Decrease");

	m_label->setTheme(Themes::getLabelTheme());
	m_plusButton->setTheme(Themes::getLabelTheme());
	m_minusButton->setTheme(Themes::getLabelTheme());

	m_plusButton->onButtonEvent(this, &IcosphereMenu::onPlusButtonEvent);
	m_minusButton->onButtonEvent(this, &IcosphereMenu::onMinusButtonEvent);
}

void IcosphereMenu::setup(int width, int posX, int posY, int paddingX, int paddingY) {
	m_plusButton->setWidth((width - 3 * paddingX) / 2);
	m_minusButton->setWidth((width - 3 * paddingX) / 2);

	m_label->setPosition(posX, posY);
	int offsetY = m_label->getHeight() + paddingY;
	m_minusButton->setPosition(posX, posY + offsetY);
	m_plusButton->setPosition(posX + m_plusButton->getWidth() + paddingX, posY + offsetY);
}

void IcosphereMenu::update() {
	m_label->update();
	m_plusButton->update();
	m_minusButton->update();
}

void IcosphereMenu::draw() {
	m_label->draw();
	m_plusButton->draw();
	m_minusButton->draw();
}

void IcosphereMenu::setActiveObject(std::vector<Object*> objects) {
	m_icospheres.clear();
	for (size_t i = 0; i < objects.size(); i++) {
		if (objects[i]->getClassName() == "Icosphere") {
			m_icospheres.push_back(dynamic_cast<Icosphere*>(objects[i]));
		}
	}
}

void IcosphereMenu::onPlusButtonEvent(ofxDatGuiButtonEvent e) {
	for (size_t i = 0; i < m_icospheres.size(); i++) {
		m_icospheres[i]->increaseSubdivision();
		m_minusButton->setEnabled(true);
		if (m_icospheres[i]->getSubdivision() >= m_icospheres[i]->getMaxSubdivision()) {
			m_plusButton->setEnabled(false);
		}
		else {
			m_plusButton->setEnabled(true);
		}
	}
}

void IcosphereMenu::onMinusButtonEvent(ofxDatGuiButtonEvent e) {
	for (size_t i = 0; i < m_icospheres.size(); i++) {
		m_icospheres[i]->decreaseSubdivision();
		m_plusButton->setEnabled(true);
		if (m_icospheres[i]->getSubdivision() <= 0) {
			m_minusButton->setEnabled(false);
		}
		else {
			m_minusButton->setEnabled(true);
		}
	}
}

IcosphereMenu::~IcosphereMenu() {
	delete m_minusButton;
	delete m_plusButton;
}