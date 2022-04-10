#include "LightingModeMenu.h"

LightingModeMenu::LightingModeMenu() {
	m_dropdown = new ofxDatGuiDropdown("Phong", { "Gouraud", "Phong", "Blinn-Phong" });
	m_font.load(Themes::getFontName(), 12);
	m_dropdown->onDropdownEvent(this, &LightingModeMenu::onDropdownEvent);
}

void LightingModeMenu::setup(int posX, int posY, int width, int padding) {
	m_dropdown->setPosition(posX, posY);
	m_dropdown->setWidth(width);

	m_dropdown->setTheme(Themes::getLabelTheme());
}

void LightingModeMenu::setObject(const std::vector<Object*>& objects) {
	m_objects.clear();
	m_objects = objects;

	if (!objects.empty()) {
		if (objects[0]->getVertexShaderName() == m_gouraudVertexShaderName) {
			m_dropdown->setLabel("Gouraud");
		}
		if (objects[0]->getVertexShaderName() == m_phongVertexShaderName) {
			m_dropdown->setLabel("Phong");
		}
		if (objects[0]->getVertexShaderName() == m_blinnPhongVertexShaderName) {
			m_dropdown->setLabel("Blinn-Phong");
		}
	}
}

void LightingModeMenu::onDropdownEvent(ofxDatGuiDropdownEvent e) {
	std::string vs;
	std::string fs;
	if (e.child == 0) {
		vs = m_gouraudVertexShaderName;
		fs = m_gouraudFragmentShaderName;
	}
	else if (e.child == 1) {
		vs = m_phongVertexShaderName;
		fs = m_phongFragmentShaderName;
	}
	else if (e.child == 2) {
		vs = m_blinnPhongVertexShaderName;
		fs = m_blinnPhongFragmentShaderName;
	}

	for (size_t i = 0; i < m_objects.size(); i++) {
		m_objects[i]->changeShaders(vs, fs);
	}
}

void LightingModeMenu::draw() {
	m_font.drawString("Lighting Model", m_dropdown->getX() + m_dropdown->getWidth() / 2.0f - 60.0f,
		m_dropdown->getY() - 15.0f);
	m_dropdown->draw();
}
void LightingModeMenu::update() {
	m_dropdown->update();
}

LightingModeMenu::~LightingModeMenu() {
	delete m_dropdown;
}