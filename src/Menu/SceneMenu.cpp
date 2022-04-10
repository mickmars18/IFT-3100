#include "SceneMenu.h"

void SceneMenu::setup(int width, int posX, int posY, int paddingX, int paddingY) {
	m_width = width;
	m_posX = posX;
	m_posY = posY;
	m_paddingX = paddingX;
	m_paddingY = paddingY;
	int textWidth = 58;
	int textHeight = 38;
	m_sceneTextPosition = ofVec2f(posX + (width - textWidth) / 2, posY + paddingY + textHeight / 2);
	setupPosition();
	m_font.load(Themes::getFontName(), 12);
}

void SceneMenu::setupPosition() {
	int buttonHeight = 0;
	int initPosY = m_posY + m_paddingY;
	for (std::list<std::pair<ofxDatGuiButton*, Object*>>::iterator it = m_buttons.begin(); it != m_buttons.end(); ++it) {
		buttonHeight += (*it).first->getHeight() + m_paddingY;
		int margin = 20 * (*it).second->getNumberOfParents();
		(*it).first->setPosition(m_posX + m_paddingX + margin, initPosY + buttonHeight);
		(*it).first->setWidth(m_width - 2 * m_paddingX - margin);
	}
}

void SceneMenu::resetObjects(std::list<Object*>& objects) {
	for (std::list<std::pair<ofxDatGuiButton*, Object*>>::iterator it = m_buttons.begin(); it != m_buttons.end(); ++it) {
		delete it->first;
	}
	m_buttons.clear();

	organiseObjectList(objects);
	for (std::list<Object*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		std::string objectName = (*it)->getName();
		ofxDatGuiButton* button = new ofxDatGuiButton(objectName);
		button->setTheme(Themes::getTextTheme());
		button->setBackgroundColorOnMouseOver(ofColor(25 * .8, 121 * .8, 202 * .8));
		button->onButtonEvent(this, &SceneMenu::onButtonClicked);
		m_buttons.push_back(std::make_pair(button, (*it)));
	}
	setupPosition();
}

void SceneMenu::organiseObjectList(std::list<Object*>& objects) {
	std::list<Object*> result;

	for (std::list<Object*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		if ((*it)->isRoot()) {
			insertNextNode(*it, result);
		}
	}
	objects = result;
}

void SceneMenu::insertNextNode(Object* node, std::list<Object*>& objects) {
	objects.push_back(node);
	std::list<Object*> children = node->getChildren();
	for (std::list<Object*>::iterator it = children.begin(); it != children.end(); ++it) {
		insertNextNode(*it, objects);
	}
}

void SceneMenu::onButtonClicked(ofxDatGuiButtonEvent e) {
	if (InputController::isKeyDown(112)) {
		std::cout << "p down" << std::endl;
		return;
	}
	for (std::list<std::pair<ofxDatGuiButton*, Object*>>::iterator it = m_buttons.begin(); it != m_buttons.end(); ++it) {
		if (e.target == (*it).first) {
			Notify((*it).second);
			break;
		}
	}
}

void SceneMenu::setObjectName(Object* object, const std::string& newName) {
	for (std::list<std::pair<ofxDatGuiButton*, Object*>>::iterator it = m_buttons.begin(); it != m_buttons.end(); ++it) {
		if (object == (*it).second) {
			(*it).first->setLabel(newName);
			break;
		}
	}
}

void SceneMenu::update() {
	setupPosition();
	for (std::list<std::pair<ofxDatGuiButton*, Object*>>::iterator it = m_buttons.begin(); it != m_buttons.end(); ++it) {
		(*it).first->update();
	}
}

void SceneMenu::draw() {
	drawRectangle();

	m_font.drawString("Scene", m_sceneTextPosition.x, m_sceneTextPosition.y);

	for (std::list<std::pair<ofxDatGuiButton*, Object*>>::iterator it = m_buttons.begin(); it != m_buttons.end(); ++it) {
		(*it).first->draw();
	}
}

void SceneMenu::drawRectangle() {
	ofSetColor(30, 30, 30);
	ofDrawRectangle(ofRectangle(m_posX, m_posY, m_width, ofGetHeight()));
	ofSetColor(255, 255, 255);
}

void SceneMenu::drawSelection(const std::vector<Object*>& object) {
	for (std::list<std::pair<ofxDatGuiButton*, Object*>>::iterator it = m_buttons.begin(); it != m_buttons.end(); ++it) {
		if (std::find(object.begin(), object.end(), (*it).second) != object.end()) {
			(*it).first->setBackgroundColor(ofColor::fromHex(0x1979ca));
			(*it).first->setStripeColor(ofColor::white);
		}
		else {
			(*it).first->setBackgroundColor(ofColor::fromHex(0x1A1A1A));
			(*it).first->setStripeColor(ofColor::black);
		}
	}
}

void SceneMenu::mousePressed(int x, int y, int button) {
	if (!(x > m_posX) || !(x < m_posX + m_width)) {
		return;
	}
	if (!(y > m_posY) || !(y < m_posY + ofGetHeight())) {
		return;
	}
	for (std::list<std::pair<ofxDatGuiButton*, Object*>>::iterator it = m_buttons.begin(); it != m_buttons.end(); ++it) {
		if ((*it).first->hitTest(ofPoint(x, y))) {
			return;
		}
	}
	Notify(nullptr);
}

SceneMenu::~SceneMenu() {
	for (std::list<std::pair<ofxDatGuiButton*, Object*>>::iterator it = m_buttons.begin(); it != m_buttons.end(); ++it) {
		delete (*it).first;
	}
}