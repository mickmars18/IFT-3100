#include "LightMenu.h"

LightMenu::LightMenu() {
	m_lightModeDropdown = new ofxDatGuiDropdown("", { "Ambient", "Directional", "Point", "Spot"});
	m_font.load(Themes::getFontName(), 12);
	m_intensitySlider = new ofxDatGuiSlider("Intensity", 0.0f, 10.0f);
	m_lightModeDropdown->onDropdownEvent(this, &LightMenu::onDropdownEvent);
	m_intensitySlider->onSliderEvent(this, &LightMenu::onIntensityChange);

	m_diffusePicker = new ofxDatGuiColorPicker("Diffuse");
	m_diffusePicker->onColorPickerEvent(this, &LightMenu::onDiffusePickerEvent);

	m_specularPicker = new ofxDatGuiColorPicker("Specular");
	m_specularPicker->onColorPickerEvent(this, &LightMenu::onSpecularPickerEvent);
}

void LightMenu::setup(int posX, int posY, int width, int padding) {
	m_padding = padding;

	m_lightModeDropdown->setPosition(posX, posY);
	m_lightModeDropdown->setWidth(width);

	m_intensitySlider->setTheme(Themes::getThemeSlider());
	m_intensitySlider->setPosition(posX, m_lightModeDropdown->getY() + m_lightModeDropdown->getHeight() + padding);
	m_intensitySlider->setWidth(width, 0.3f);

	m_lightModeDropdown->setTheme(Themes::getLabelTheme());

	m_diffusePicker->setTheme(Themes::getLabelTheme());
	m_diffusePicker->setPosition(posX, m_intensitySlider->getY() + m_intensitySlider->getHeight() + padding);
	m_diffusePicker->setWidth(width, 0.3f);

	m_specularPicker->setTheme(Themes::getLabelTheme());
	m_specularPicker->setPosition(posX, m_diffusePicker->getY() + m_diffusePicker->getHeight() + padding);
	m_specularPicker->setWidth(width, 0.3f);
}

void LightMenu::onIntensityChange(ofxDatGuiSliderEvent e) {
	if (!m_objects.empty() && m_objects[0]->getClassName() == "Light") {
		for (size_t i = 0; i < m_objects.size(); i++) {
			dynamic_cast<Light*>(m_objects[i])->setIntensity(e.value);
		}
	}
}

void LightMenu::onDiffusePickerEvent(ofxDatGuiColorPickerEvent e) {
	if (!m_objects.empty() && m_objects[0]->getClassName() == "Light") {
		for (size_t i = 0; i < m_objects.size(); i++) {
			dynamic_cast<Light*>(m_objects[i])->setDiffuseColor((float)e.color.r / 255.0f, (float)e.color.g / 255.0f, (float)e.color.b / 255.0f);
		}
	}
}
void LightMenu::onSpecularPickerEvent(ofxDatGuiColorPickerEvent e) {
	if (!m_objects.empty() && m_objects[0]->getClassName() == "Light") {
		for (size_t i = 0; i < m_objects.size(); i++) {
			dynamic_cast<Light*>(m_objects[i])->setSpecularColor((float)e.color.r / 255.0f, (float)e.color.g / 255.0f, (float)e.color.b / 255.0f);
		}
	}
}

void LightMenu::setLightController(LightsController* lightController) {
	m_lightController = lightController;
}

void LightMenu::setObject(const std::vector<Object*>& objects) {
	m_objects.clear();
	m_objects = objects;

	if (!objects.empty() && objects[0]->getClassName() == "Light") {
		Light* light = dynamic_cast<Light*>(objects[0]);
		if (light->getMode() == LightMode::Ambient)
			m_lightModeDropdown->setLabel("Ambient");
		else if (light->getMode() == LightMode::Directional)
			m_lightModeDropdown->setLabel("Directional");
		else if (light->getMode() == LightMode::Point)
			m_lightModeDropdown->setLabel("Point");
		else if (light->getMode() == LightMode::Spot)
			m_lightModeDropdown->setLabel("Spot");

		m_intensitySlider->setValue(light->getIntensity());

		glm::vec3 diffuseColor = light->getDiffuseColor();
		m_diffusePicker->setColor(diffuseColor.r * 255.0f, diffuseColor.g * 255.0f, diffuseColor.b * 255.0f);

		glm::vec3 specularColor = light->getSpecularColor();
		m_specularPicker->setColor(specularColor.r * 255.0f, specularColor.g * 255.0f, specularColor.b * 255.0f);
	}
}

void LightMenu::onDropdownEvent(ofxDatGuiDropdownEvent e) {
	if (e.child == 0) {
		for (size_t i = 0; i < m_objects.size(); i++) {
			Light* light = dynamic_cast<Light*>(m_objects[i]);
			m_lightController->changeLightMode(light, LightMode::Ambient);
		}
	}
	else if (e.child == 1) {
		for (size_t i = 0; i < m_objects.size(); i++) {
			Light* light = dynamic_cast<Light*>(m_objects[i]);
			m_lightController->changeLightMode(light, LightMode::Directional);
		}
	}
	else if (e.child == 2) {
		for (size_t i = 0; i < m_objects.size(); i++) {
			Light* light = dynamic_cast<Light*>(m_objects[i]);
			m_lightController->changeLightMode(light, LightMode::Point);
		}
	}
	else if (e.child == 3) {
		for (size_t i = 0; i < m_objects.size(); i++) {
			Light* light = dynamic_cast<Light*>(m_objects[i]);
			m_lightController->changeLightMode(light, LightMode::Spot);
		}
	}
}

void LightMenu::draw() {
	m_font.drawString("Light Options", m_lightModeDropdown->getX() + m_lightModeDropdown->getWidth() / 2.0f - 60.0f,
		m_lightModeDropdown->getY() - 15.0f);
	m_intensitySlider->draw();
	m_diffusePicker->draw();
	m_specularPicker->draw();
	m_lightModeDropdown->draw();
}
void LightMenu::update() {
	m_intensitySlider->update();
	m_diffusePicker->update();
	m_specularPicker->update();
	m_lightModeDropdown->update();

	int yOffset = 0;
	if (m_diffusePicker->getFocused())
		yOffset = 80;
	m_specularPicker->setPosition(m_diffusePicker->getX(), m_diffusePicker->getY() + m_diffusePicker->getHeight() + m_padding + yOffset);
}

LightMenu::~LightMenu() {
	delete m_lightModeDropdown;
	delete m_intensitySlider;
	delete m_diffusePicker;
	delete m_specularPicker;
}