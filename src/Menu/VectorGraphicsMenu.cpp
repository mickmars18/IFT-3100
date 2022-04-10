#include "VectorGraphicsMenu.h"

VectorGraphicsMenu::VectorGraphicsMenu() {
	m_slider = new ofxDatGuiSlider("Line width", 0, 10, m_lineWidth);
	m_slider->onSliderEvent(this, &VectorGraphicsMenu::onSliderEvent);

	m_lineColorPicker = new ofxDatGuiColorPicker("Line color", ofColor::black);
	m_fillColorPicker = new ofxDatGuiColorPicker("Filling", ofColor::white);
	m_backgroundColorPicker = new ofxDatGuiColorPicker("Background", ofColor::black);

	m_backgroundColorPicker->onColorPickerEvent(this, &VectorGraphicsMenu::onBackgroundColorPickerEvent);
	m_fillColorPicker->onColorPickerEvent(this, &VectorGraphicsMenu::onFillColorPickerEvent);
	m_lineColorPicker->onColorPickerEvent(this, &VectorGraphicsMenu::onLineColorPickerEvent);
}

void VectorGraphicsMenu::setBackground(Background* background) {
	m_background = background;
	m_backgroundColorPicker->setColor(m_background->getColor());
}

void VectorGraphicsMenu::setVectorGraphicsInitializer(VectorGraphicsInitializer* vectorGraphicsInitializer) {
	m_vectorGraphicsInitializer = vectorGraphicsInitializer;
}

void VectorGraphicsMenu::setup(int width, int posX, int posY, int paddingX, int paddingY) {
	m_width = width - 2 * paddingX;
	m_posX = posX;
	m_posY = posY;
	m_paddingX = paddingX;
	m_paddingY = paddingY;

	m_slider->setTheme(Themes::getThemeSlider());
	m_lineColorPicker->setTheme(Themes::getThemeSlider());
	m_fillColorPicker->setTheme(Themes::getThemeSlider());
	m_backgroundColorPicker->setTheme(Themes::getThemeSlider());

	m_slider->setWidth(width, 0.28f);
	int totalHeight = m_slider->getHeight() + 3 * m_lineColorPicker->getHeight() + 4 * m_paddingY + 3 * m_colorPickerExpendedHeight;
	m_slider->setPosition(posX, ofGetWindowHeight() - totalHeight);

	resetColorPickersPosition();
}

void VectorGraphicsMenu::resetColorPickersPosition() {
	m_lineColorPicker->setWidth(m_width, 0.28f);
	int posY = m_slider->getY() + m_slider->getHeight() + m_paddingY;
	m_lineColorPicker->setPosition(m_posX, posY);

	m_fillColorPicker->setWidth(m_width, 0.28f);
	posY = m_lineColorPicker->getY() + m_lineColorPicker->getHeight() + m_paddingY + m_colorPickerExpendedHeight;
	m_fillColorPicker->setPosition(m_posX, posY);

	m_backgroundColorPicker->setWidth(m_width, 0.32f);
	posY = m_fillColorPicker->getY() + m_fillColorPicker->getHeight() + m_paddingY + m_colorPickerExpendedHeight;
	m_backgroundColorPicker->setPosition(m_posX, posY);

	int totalHeight = m_backgroundColorPicker->getY() + m_backgroundColorPicker->getHeight() - m_slider->getY();

}

void VectorGraphicsMenu::onSliderEvent(ofxDatGuiSliderEvent e) {
	int value = (int)e.value;
	m_vectorGraphicsInitializer->setLineWidth(value);
}

void VectorGraphicsMenu::onBackgroundColorPickerEvent(ofxDatGuiColorPickerEvent e) {
	m_background->setColor(e.color);
}

void VectorGraphicsMenu::onFillColorPickerEvent(ofxDatGuiColorPickerEvent e) {
	m_vectorGraphicsInitializer->setFillColor(e.color);
}

void VectorGraphicsMenu::onLineColorPickerEvent(ofxDatGuiColorPickerEvent e) {
	m_vectorGraphicsInitializer->setLineColor(e.color);
}

void VectorGraphicsMenu::update() {
	m_slider->update();
	m_lineColorPicker->update();
	m_fillColorPicker->update();
	m_backgroundColorPicker->update();
}

void VectorGraphicsMenu::draw() {
	m_slider->draw();
	m_lineColorPicker->draw();
	m_fillColorPicker->draw();
	m_backgroundColorPicker->draw();
}

VectorGraphicsMenu::~VectorGraphicsMenu() {
	delete m_slider;
	delete m_lineColorPicker;
	delete m_fillColorPicker;
	delete m_backgroundColorPicker;
}