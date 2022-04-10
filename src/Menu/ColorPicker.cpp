#include "ColorPicker.h"

ColorPicker::ColorPicker() {
	m_label = new ofxDatGuiLabel("Color :");
	m_label->setTheme(Themes::getLabelTheme());

	m_colorPicker = new ofxDatGuiColorPicker("COLOR", ofColor::fromHex(0xFFFFFF));
	m_colorPicker->onColorPickerEvent(this, &ColorPicker::onColorPickerEvent);

	m_showPicker = false;
	m_showRGB = false;
	m_showHSB = false;
	m_togglePicker = new ofxDatGuiToggle("PICKER", m_showPicker);
	m_toggleRGB = new ofxDatGuiToggle("RGB", m_showRGB);
	m_toggleHSB = new ofxDatGuiToggle("HSB", m_showHSB);
	m_togglePicker->setChecked(m_showPicker);
	m_toggleRGB->setChecked(m_showRGB);
	m_toggleHSB->setChecked(m_showHSB);

	m_togglePicker->onButtonEvent(this, &ColorPicker::onTogglePicker);
	m_toggleRGB->onButtonEvent(this, &ColorPicker::onToggleRGB);
	m_toggleHSB->onButtonEvent(this, &ColorPicker::onToggleHSB);

	m_sliderRed = new ofxDatGuiSlider("RED", 0, 255, 255);
	m_sliderGreen = new ofxDatGuiSlider("GREEN", 0, 255, 255);
	m_sliderBlue = new ofxDatGuiSlider("BLUE", 0, 255, 255);

	m_sliderHue = new ofxDatGuiSlider("HUE", 0, 360.0f, 0);
	m_sliderSaturation = new ofxDatGuiSlider("SATURATION", 0.0f, 100.0f, 0.0f);
	m_sliderBrightness = new ofxDatGuiSlider("BRIGHTNESS", 0.0f, 100.0f, 100.0f);

	setupThemes();

	m_toggleRGB->setTheme(Themes::getTextTheme());
	m_toggleHSB->setTheme(Themes::getTextTheme());
	m_togglePicker->setTheme(Themes::getTextTheme());

	m_toggleRGB->setStripeColor(ofColor::white);
	m_togglePicker->setStripeColor(ofColor::white);
	m_toggleHSB->setStripeColor(ofColor::white);
	m_sliderRed->setStripeColor(ofColor::white);
	m_sliderGreen->setStripeColor(ofColor::white);
	m_sliderBlue->setStripeColor(ofColor::white);
	m_sliderHue->setStripeColor(ofColor::white);
	m_sliderSaturation->setStripeColor(ofColor::white);
	m_sliderBrightness->setStripeColor(ofColor::white);
	m_colorPicker->setStripeColor(ofColor::white);

	m_sliderRed->onSliderEvent(this, &ColorPicker::onRedChange);
	m_sliderGreen->onSliderEvent(this, &ColorPicker::onGreenChange);
	m_sliderBlue->onSliderEvent(this, &ColorPicker::onBlueChange);

	m_sliderHue->onSliderEvent(this, &ColorPicker::onHueChange);
	m_sliderSaturation->onSliderEvent(this, &ColorPicker::onSaturationChange);
	m_sliderBrightness->onSliderEvent(this, &ColorPicker::onBrightnessChange);
}

void ColorPicker::setupColorPicker(int posY, int width, int paddingX, int paddingY) {
	m_label->setWidth(width - paddingX * 2);
	m_label->setPosition(paddingX, posY);

	m_posY = m_label->getY() + m_label->getHeight() + paddingY;
	m_width = width;
	m_paddingX = paddingX;
	m_paddingY = paddingY;

	int togglesWidth = (width - paddingX * 4) / 3;

	m_toggleRGB->setPosition(paddingX, m_posY);
	m_toggleRGB->setWidth(togglesWidth, 0.25f);

	m_toggleHSB->setPosition(paddingX * 2 + togglesWidth, m_posY);
	m_toggleHSB->setWidth(togglesWidth, 0.25f);

	m_togglePicker->setPosition(paddingX * 3 + 2 * togglesWidth, m_posY);
	m_togglePicker->setWidth(togglesWidth, 0.25f);

	m_colorPicker->setWidth(width - paddingX * 2, 0.25f);

	m_sliderRed->setWidth(m_width - m_paddingX * 2, 0.25f);
	m_sliderGreen->setWidth(m_width - m_paddingX * 2, 0.25f);
	m_sliderBlue->setWidth(m_width - m_paddingX * 2, 0.25f);

	m_sliderHue->setWidth(m_width - m_paddingX * 2, 0.25f);
	m_sliderSaturation->setWidth(m_width - m_paddingX * 2, 0.25f);
	m_sliderBrightness->setWidth(m_width - m_paddingX * 2, 0.25f);

	calculateSlidersPositions();
}

void ColorPicker::setupThemes() {
	m_sliderRedTheme = m_sliderRed->getTheme();
	m_sliderGreenTheme = m_sliderGreen->getTheme();
	m_sliderBlueTheme = m_sliderBlue->getTheme();

	m_sliderRedTheme.color.slider.fill = ofColor(180, 40, 40);
	m_sliderGreenTheme.color.slider.fill = ofColor(40, 180, 40);
	m_sliderBlueTheme.color.slider.fill = ofColor(30, 30, 200);

	m_sliderRed->setTheme(&m_sliderRedTheme);
	m_sliderGreen->setTheme(&m_sliderGreenTheme);
	m_sliderBlue->setTheme(&m_sliderBlueTheme);
}

void ColorPicker::calculateSlidersPositions() {
	m_height = m_toggleRGB->getY() + m_toggleRGB->getHeight() + m_paddingY;

	m_sliderRed->setPosition(m_paddingX, m_height);
	m_sliderGreen->setPosition(m_paddingX, m_sliderRed->getY() + m_sliderRed->getHeight() + m_paddingY / 2);
	m_sliderBlue->setPosition(m_paddingX, m_sliderGreen->getY() + m_sliderGreen->getHeight() + m_paddingY / 2);

	if (m_showRGB) {
		m_height += m_sliderRed->getHeight() * 3 + m_paddingY * 3;
	}

	m_sliderHue->setPosition(m_paddingX, m_height);
	m_sliderSaturation->setPosition(m_paddingX, m_sliderHue->getY() + m_sliderHue->getHeight() + m_paddingY / 2);
	m_sliderBrightness->setPosition(m_paddingX, m_sliderSaturation->getY() + m_sliderSaturation->getHeight() + m_paddingY / 2);

	if (m_showHSB) {
		m_height += m_sliderHue->getHeight() * 3 + m_paddingY * 3;
	}

	m_colorPicker->setPosition(m_paddingX, m_height + m_paddingY);
}

void ColorPicker::setActiveObject(const std::vector<Object*>& object) {
	m_activeObject = object;
	for (size_t i = 0; i < m_activeObject.size(); i++) {
		m_drawColor = m_activeObject[i]->getColor();
	}
	setColorPickerColors();
	setRGBColors();
	setHSBColors();
}

void ColorPicker::onTogglePicker(ofxDatGuiButtonEvent e) {
	m_showPicker = !m_showPicker;
	m_togglePicker->setChecked(m_showPicker);
	calculateSlidersPositions();
}

void ColorPicker::onToggleRGB(ofxDatGuiButtonEvent e) {
	m_showRGB = !m_showRGB;
	m_toggleRGB->setChecked(m_showRGB);
	calculateSlidersPositions();
}

void ColorPicker::onToggleHSB(ofxDatGuiButtonEvent e) {
	m_showHSB = !m_showHSB;
	m_toggleHSB->setChecked(m_showHSB);
	calculateSlidersPositions();
}

void ColorPicker::onRedChange(ofxDatGuiSliderEvent e) {
	int newRedValue = (int)e.value;
	m_sliderRed->setValue(newRedValue, false);
	m_drawColor.r = newRedValue;
	setColor();
	setColorPickerColors();
	setHSBColors();
}

void ColorPicker::onGreenChange(ofxDatGuiSliderEvent e) {
	int newGreenValue = (int)e.value;
	m_sliderGreen->setValue(newGreenValue, false);
	m_drawColor.g = newGreenValue;
	setColor();
	setColorPickerColors();
	setHSBColors();
}

void ColorPicker::onBlueChange(ofxDatGuiSliderEvent e) {
	int newBlueValue = (int)e.value;
	m_sliderBlue->setValue(newBlueValue, false);
	m_drawColor.b = newBlueValue;
	setColor();
	setColorPickerColors();
	setHSBColors();
}

void ColorPicker::onHueChange(ofxDatGuiSliderEvent e) {
	int newHueValue = (int)e.value;
	m_sliderHue->setValue(newHueValue, false);
	int* rgb = ColorSpace::HSBtoRGB(newHueValue, m_sliderSaturation->getValue() / 100.0f, m_sliderBrightness->getValue() / 100.0f);
	m_drawColor = ofColor(rgb[0], rgb[1], rgb[2]);
	setColor();
	setColorPickerColors();
	setRGBColors();
}
void ColorPicker::onSaturationChange(ofxDatGuiSliderEvent e) {
	int newSaturationValue = e.value;
	m_sliderSaturation->setValue(newSaturationValue, false);
	int* rgb = ColorSpace::HSBtoRGB(m_sliderHue->getValue(), newSaturationValue / 100.0f, m_sliderBrightness->getValue() / 100.0f);
	m_drawColor = ofColor(rgb[0], rgb[1], rgb[2]);
	setColor();
	setColorPickerColors();
	setRGBColors();
}
void ColorPicker::onBrightnessChange(ofxDatGuiSliderEvent e) {
	int newBrightnessValue = e.value;
	m_sliderBrightness->setValue(newBrightnessValue, false);
	int* rgb = ColorSpace::HSBtoRGB(m_sliderHue->getValue(), m_sliderSaturation->getValue() / 100.0f, newBrightnessValue / 100.0f);
	m_drawColor = ofColor(rgb[0], rgb[1], rgb[2]);
	setColor();
	setColorPickerColors();
	setRGBColors();
}

void ColorPicker::onColorPickerEvent(ofxDatGuiColorPickerEvent e) {
	m_drawColor = e.color;
	setColor();
	setRGBColors();
	setHSBColors();
}

void ColorPicker::setColor() {
	for (size_t i = 0; i < m_activeObject.size(); i++) {
		m_activeObject[i]->changeColor(m_drawColor);
	}
}
void ColorPicker::setColorPickerColors() {
	m_colorPicker->setColor(m_drawColor);
}

void ColorPicker::setRGBColors() {
	m_sliderRed->setValue(m_drawColor.r, false);
	m_sliderGreen->setValue(m_drawColor.g, false);
	m_sliderBlue->setValue(m_drawColor.b, false);
}

void ColorPicker::setHSBColors() {
	float* hsb = ColorSpace::RGBtoHSB(m_drawColor.r, m_drawColor.g, m_drawColor.b);
	m_sliderHue->setValue((int)hsb[0], false);
	m_sliderSaturation->setValue(int(hsb[1] * 100.0f), false);
	m_sliderBrightness->setValue(int(hsb[2] * 100.0f), false);
}

void ColorPicker::setColor(ofColor color) {
	m_colorPicker->setColor(color);
}

int ColorPicker::getHeight() const {
	if (m_showPicker)
		return m_colorPicker->getY() + m_colorPicker->getHeight();
	if (m_showHSB)
		return m_sliderBrightness->getY() + m_sliderBrightness->getHeight();
	if (m_showRGB)
		return m_sliderBlue->getY() + m_sliderBlue->getHeight();
	else
		return m_toggleRGB->getY() + m_toggleRGB->getHeight();
}

void ColorPicker::update() {
	m_label->update();
	m_togglePicker->update();
	m_toggleRGB->update();
	m_toggleHSB->update();
	if(m_showPicker)
		m_colorPicker->update();

	if (m_showRGB) {
		m_sliderRed->update();
		m_sliderGreen->update();
		m_sliderBlue->update();
	}

	if (m_showHSB) {
		m_sliderHue->update();
		m_sliderSaturation->update();
		m_sliderBrightness->update();
	}
}

void ColorPicker::draw() {
	m_label->draw();
	m_togglePicker->draw();
	m_toggleRGB->draw();
	m_toggleHSB->draw();
	if (m_showPicker)
		m_colorPicker->draw();

	if (m_showRGB) {
		m_sliderRed->draw();
		m_sliderGreen->draw();
		m_sliderBlue->draw();
	}

	if (m_showHSB) {
		m_sliderHue->draw();
		m_sliderSaturation->draw();
		m_sliderBrightness->draw();
	}
}

int ColorPicker::getBottomCoord() const {
	if (m_showPicker)
		return m_colorPicker->getY() + m_colorPicker->getHeight();
	else if (m_showHSB)
		return m_sliderHue->getY() + m_sliderHue->getHeight();
	else if (m_showRGB)
		return m_sliderRed->getY() + m_sliderRed->getHeight();
	else
		return m_toggleRGB->getY() + m_toggleRGB->getHeight();
}

ColorPicker::~ColorPicker() {
	delete m_label;
	delete m_colorPicker;
	delete m_togglePicker;
	delete m_toggleRGB;
	delete m_toggleHSB;
	delete m_sliderRed;
	delete m_sliderGreen;
	delete m_sliderBlue;
	delete m_sliderHue;
	delete m_sliderSaturation;
	delete m_sliderBrightness;
}