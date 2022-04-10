#include "Menu.h"
#include <iostream>
#include "Themes.h"

Menu::Menu() {
	m_name = new ofxDatGuiTextInput("Name");

	std::vector<Object*> m_activeObject;

	m_name->onTextInputEvent(this, &Menu::nameChanged);

	m_imageSamplingSlider = new ImageSamplingSlider();
	m_shininessSlider = new ShininessSlider();
	m_vectorGraphicsMenu = new VectorGraphicsMenu();
	m_cursor = new Cursor();
	m_icosphereMenu = new IcosphereMenu();
}

void Menu::setup(int width, int paddingX, int paddingY) {
	m_width = width;
	m_paddingX = paddingX;
	m_paddingY = paddingY;

	m_name->setWidth(m_width - m_paddingX * 2, .2);
	m_name->setPosition(m_paddingX, m_paddingY);

	m_name->setTheme(Themes::getTextTheme());
	m_name->setStripeColor(ofColor::white);

	int scenePosY = m_colorPicker.getHeight();

	m_sceneMenu.setup(width, ofGetWidth() - width, 0, paddingX, paddingY);
	m_sceneMenu.Attach(this);

	m_transformMenu.setup(width, m_name->getY() + m_name->getHeight() + 3 * m_paddingY, paddingX, paddingY);
	m_colorPicker.setupColorPicker(m_transformMenu.getBottomCoord().y + 3 * m_paddingY, m_width, m_paddingX, m_paddingY);

	m_imageSamplingSlider->setup(m_width, m_paddingX, m_transformMenu.getBottomCoord().y + m_paddingY, m_paddingX, m_paddingY);
	m_vectorGraphicsMenu->setup(width, ofGetWindowWidth() - width + paddingX, ofGetWindowHeight() - 300, paddingX, paddingY);
	m_randomizeButton.setup(paddingX, m_transformMenu.getBottomCoord().y + 3 * m_paddingY, width - paddingX * 2);
	m_icosphereMenu->setup(m_width, paddingX, m_transformMenu.getBottomCoord().y + 3 * m_paddingY, paddingX, paddingY);

	float toneMappingMenuHeight = 100.0f;
	m_toneMappingMenu.setup(paddingX, ofGetWindowHeight() - toneMappingMenuHeight - paddingY, width - 2 * paddingX, toneMappingMenuHeight, paddingY);

	m_lightingModeMenu.setup(paddingX, ofGetWindowHeight() - 120, width - 2 * paddingX, paddingX);
	m_lightMenu.setup(paddingX, ofGetWindowHeight() - 300, width - 2 * paddingX, paddingX);

	m_shininessSlider->setup(m_paddingX, m_transformMenu.getBottomCoord().y + m_paddingY, m_width - 2 * m_paddingX);

	m_RT_Menu.setup(paddingX, ofGetWindowHeight() - 200, width - 2 * paddingX, paddingX);
	m_delaunayMenu.setup(width - 2.0f * paddingX, paddingX, ofGetWindowHeight() - 150, paddingX, paddingY);

	m_noiseTextureMenu.setup(width - 2.0f * paddingX, ofGetWidth() - width, ofGetWindowHeight() - 120, paddingX, paddingY);

	m_PBR_Menu.setup(paddingX, ofGetWindowHeight() - 300, width - 2.0f * paddingX, paddingX);
}

void Menu::setBackgroundToVectorGraphicsMenu(Background* background) {
	m_vectorGraphicsMenu->setBackground(background);
}

void Menu::setVectorGraphicsInitializer(VectorGraphicsInitializer* vectorGraphicsInitializer) {
	m_vectorGraphicsMenu->setVectorGraphicsInitializer(vectorGraphicsInitializer);
}

void Menu::mouseMoved(int x, int y) {
	m_transformMenu.mouseMoved(x, y);
}

void Menu::mousePressed(int x, int y, int button) {
	m_transformMenu.mousePressed(x, y, button);
	m_sceneMenu.mousePressed(x, y, button);
}

void Menu::mouseReleased(int x, int y, int button) {
	m_transformMenu.mouseReleased(x, y, button);
}

void Menu::mouseDragged(int x, int y, int button) {
	m_transformMenu.mouseDragged(x, y, button);
}

void Menu::keyReleased(int key) {
	m_transformMenu.keyReleased(key);
}

void Menu::setActiveObject(Object* object) {
	if (object == nullptr) {
		for (size_t i = 0; i < m_activeObject.size(); i++) {
			m_activeObject[i]->setActive(false);
		}
		m_activeObject.clear();
		notifyActiveObjectChanged();
		return;
	}
	if (!InputController::isKeyDown(KEY::CTRL)) {
		for (size_t i = 0; i < m_activeObject.size(); i++) {
			m_activeObject[i]->setActive(false);
		}
		m_activeObject.clear();
		notifyActiveObjectChanged();
	}
	if (InputController::isKeyDown(KEY::CTRL)) {
		for (size_t i = 0; i < m_activeObject.size(); i++)
		{
			if (m_activeObject[i] == object) {
				object->setActive(false);
				m_activeObject.erase(m_activeObject.begin() + i);
				notifyActiveObjectChanged();
				return;
			}
		}
	}

	object->setActive(true);
	m_activeObject.push_back(object);
	m_name->setText(object->getName());

	notifyActiveObjectChanged();
}

void Menu::notifyActiveObjectChanged() {
	m_transformMenu.setActiveObject(m_activeObject);
	m_colorPicker.setActiveObject(m_activeObject);
	m_randomizeButton.setObjects(m_activeObject);
	m_icosphereMenu->setActiveObject(m_activeObject);
	m_lightingModeMenu.setObject(m_activeObject);
	m_lightMenu.setObject(m_activeObject);
	m_shininessSlider->setObject(m_activeObject);
	m_delaunayMenu.setObjects(m_activeObject);
	m_PBR_Menu.setObjects(m_activeObject);
}

bool Menu::objectInActiveObjects(Object* object) {
	for (size_t i = 0; i < m_activeObject.size(); i++) {
		if (m_activeObject[i] == object)
			return true;
	}
	return false;
}

void Menu::nameChanged(ofxDatGuiTextInputEvent e) {
	std::cout << "Name changed" << std::endl;
	for (size_t i = 0; i < m_activeObject.size(); i++) {
		m_activeObject[i]->setName(e.text);
		m_sceneMenu.setObjectName(m_activeObject[i], e.text);
	}
}

void Menu::setObjects(std::list<Object*> objects) {
	m_sceneMenu.resetObjects(objects);
}

void Menu::updateActiveObject(Object* object) {
	setActiveObject(object);
}

void Menu::resetSceneMenu(std::list<Object*>& objects) {
	m_sceneMenu.resetObjects(objects);
	m_activeObject.clear();
}

void Menu::setImageSamplingObject(ImageSampling* imageSampling) {
	m_imageSamplingSlider->setObject(imageSampling);
}

void Menu::update() {
	m_name->update();
	m_transformMenu.update();
	
	if (m_activeObject.empty()) {
		m_name->setText("_");
		m_name->setEnabled(false);
		m_transformMenu.setEnabled(false);
	}
	else {
		m_name->setEnabled(true);
		m_transformMenu.setEnabled(true);
	}

	if (atLeastOneObjectHasColorAttribute()) {
		m_colorPicker.update();
	}
	if (activeObjectsAreAllClass("ImageSampling")) {
		m_imageSamplingSlider->update();
	}

	m_sceneMenu.update();
	if (m_vectorGraphicsMode)
		m_vectorGraphicsMenu->update();

	m_cursor->update();
	if (atLeastOneActiveObjectIsOfClass("StripedCircles") || atLeastOneActiveObjectIsOfClass("GeometricPattern"))
		m_randomizeButton.update();

	if (activeObjectsAreAllClass("Icosphere"))
		m_icosphereMenu->update();

	if(m_showToneMappingMenu)
		m_toneMappingMenu.update();

	if (activeObjectsAreAllClass("Model")) {
		m_lightingModeMenu.update();
		m_shininessSlider->update();
	}

	if (activeObjectsAreAllClass("Light"))
		m_lightMenu.update();

	if (m_RT_Mode)
		m_RT_Menu.update();

	if (activeObjectsAreAllClass("Delaunay"))
		m_delaunayMenu.update();

	if (m_showNoiseTextureMenu)
		m_noiseTextureMenu.update();

	if (activeObjectsAreAllClass("PBR_Model"))
		m_PBR_Menu.update();
}

bool Menu::atLeastOneObjectHasColorAttribute() const {
	if (m_activeObject.empty())
		return false;

	for (size_t i = 0; i < m_activeObject.size(); i++) {
		if (m_activeObject[i]->hasColorAttribute())
			return true;
	}
	return false;
}

bool Menu::activeObjectsAreAllClass(const std::string& className) {
	if (m_activeObject.empty())
		return false;

	for (size_t i = 0; i < m_activeObject.size(); i++) {
		if (m_activeObject[i]->getClassName() != className)
			return false;
	}
	return true;
}

bool Menu::atLeastOneActiveObjectIsOfClass(const std::string& className) {
	for (size_t i = 0; i < m_activeObject.size(); i++) {
		if (m_activeObject[i]->getClassName() == className)
			return true;
	}
	return false;
}

void Menu::draw() {
	ofEnableBlendMode(OF_BLENDMODE_DISABLED);
	drawRectangle();
	m_name->draw();
	m_transformMenu.draw();

	if (atLeastOneObjectHasColorAttribute()) {
		m_colorPicker.draw();
	}
	if (activeObjectsAreAllClass("ImageSampling")) {
		m_imageSamplingSlider->draw();
	}

	m_sceneMenu.draw();
	m_sceneMenu.drawSelection(getActiveObject());
	if (m_vectorGraphicsMode)
		m_vectorGraphicsMenu->draw();
	m_cursor->draw();
	if (atLeastOneActiveObjectIsOfClass("StripedCircles") || atLeastOneActiveObjectIsOfClass("GeometricPattern"))
		m_randomizeButton.draw();
	
	if(activeObjectsAreAllClass("Icosphere"))
		m_icosphereMenu->draw();

	m_axisGizmo.draw(m_width);

	if (m_showToneMappingMenu)
		m_toneMappingMenu.draw();

	if (activeObjectsAreAllClass("Model")) {
		m_lightingModeMenu.draw();
		m_shininessSlider->draw();
	}

	if (activeObjectsAreAllClass("Light"))
		m_lightMenu.draw();

	if (m_RT_Mode)
		m_RT_Menu.draw();

	if (activeObjectsAreAllClass("Delaunay"))
		m_delaunayMenu.draw();

	if (m_showNoiseTextureMenu)
		m_noiseTextureMenu.draw();

	if (activeObjectsAreAllClass("PBR_Model"))
		m_PBR_Menu.draw();
}

void Menu::drawRectangle() {
	ofSetColor(30, 30, 30);
	ofDrawRectangle(ofRectangle(0, 0, m_width, ofGetHeight()));
	ofSetColor(255, 255, 255);
}

void Menu::setLightController(LightsController* lightController) {
	m_lightMenu.setLightController(lightController);
}

Menu::~Menu() {
	delete m_inputTheme;
	delete m_imageSamplingSlider;
	delete m_cursor;
	delete m_vectorGraphicsMenu;
	delete m_shininessSlider;
}