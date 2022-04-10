#include "ShininessSlider.h"

ShininessSlider::ShininessSlider() {
	m_font.load(Themes::getFontName(), 12);
	m_shininessSlider = new ofxDatGuiSlider("Shininess", 0.0f, 5.0f);
	m_shininessSlider->setTheme(Themes::getThemeSlider());
	m_shininessSlider->onSliderEvent(this, &ShininessSlider::onChange);
}

void ShininessSlider::setup(int posX, int posY, int width) {
	m_shininessSlider->setPosition(posX, posY);
	m_shininessSlider->setWidth(width, 0.3f);
}

void ShininessSlider::setObject(const std::vector<Object*>& objects) {
	m_objects.clear();
	m_objects = objects;
	if (!objects.empty() && objects[0]->getClassName() == "Model") {
		float shininess = (dynamic_cast<Model*>(objects[0]))->getShininess();
		m_shininessSlider->setValue(inverseShininess(shininess));
	}
}

float ShininessSlider::transformShininess(float shininess) {
	if (shininess == 0.0f)
		return 100.0f;

	return 1.0f / shininess;
}

float ShininessSlider::inverseShininess(float shininess) {
	if (shininess >= 100.0f)
		return 0.0f;

	return 1.0f / shininess;
}

void ShininessSlider::draw() {
	m_shininessSlider->draw();
}
void ShininessSlider::update() {
	m_shininessSlider->update();
}

void ShininessSlider::onChange(ofxDatGuiSliderEvent e) {
	for (size_t i = 0; i < m_objects.size(); i++) {
		if(m_objects[i]->getClassName() == "Model")
			(dynamic_cast<Model*>(m_objects[i]))->setShininess(transformShininess(e.value));
	}
}

ShininessSlider::~ShininessSlider() {
	delete m_shininessSlider;
}