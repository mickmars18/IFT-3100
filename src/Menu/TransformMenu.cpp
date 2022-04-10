#include "TransformMenu.h"

TransformMenu::TransformMenu() {
	m_positionLabel = new ofxDatGuiLabel("Position");
	m_positionLabel->setTheme(Themes::getTextTheme());
	m_positionXInput = new ofxDatGuiTextInput("X", "0");
	m_positionYInput = new ofxDatGuiTextInput("Y", "0");
	m_positionZInput = new ofxDatGuiTextInput("Z", "0");

	m_rotationLabel = new ofxDatGuiLabel("Rotation");
	m_rotationLabel->setTheme(Themes::getTextTheme());
	m_rotationXInput = new ofxDatGuiTextInput("X", "0");
	m_rotationYInput = new ofxDatGuiTextInput("Y", "0");
	m_rotationZInput = new ofxDatGuiTextInput("Z", "0");

	m_scaleLabel = new ofxDatGuiLabel("Scale");
	m_scaleLabel->setTheme(Themes::getTextTheme());
	m_scaleXInput = new ofxDatGuiTextInput("X", "1.0");
	m_scaleYInput = new ofxDatGuiTextInput("Y", "1.0");
	m_scaleZInput = new ofxDatGuiTextInput("Z", "1.0");

	ofxDatGuiTheme* theme = Themes::getTextThemeSmall();
	m_positionXInput->setTheme(theme);
	m_positionYInput->setTheme(theme);
	m_positionZInput->setTheme(theme);

	m_rotationXInput->setTheme(theme);
	m_rotationYInput->setTheme(theme);
	m_rotationZInput->setTheme(theme);

	m_scaleXInput->setTheme(theme);
	m_scaleYInput->setTheme(theme);
	m_scaleZInput->setTheme(theme);

	m_positionXInput->setStripeColor(ofColor(180, 40, 40));
	m_positionYInput->setStripeColor(ofColor(40, 180, 40));
	m_positionZInput->setStripeColor(ofColor(30, 30, 200));

	m_rotationXInput->setStripeColor(ofColor(180, 40, 40));
	m_rotationYInput->setStripeColor(ofColor(40, 180, 40));
	m_rotationZInput->setStripeColor(ofColor(30, 30, 200));

	m_scaleXInput->setStripeColor(ofColor(180, 40, 40));
	m_scaleYInput->setStripeColor(ofColor(40, 180, 40));
	m_scaleZInput->setStripeColor(ofColor(30, 30, 200));

	m_positionXInput->onTextInputEvent(this, &TransformMenu::onPositionXChanged);
	m_positionYInput->onTextInputEvent(this, &TransformMenu::onPositionYChanged);
	m_positionZInput->onTextInputEvent(this, &TransformMenu::onPositionZChanged);

	m_rotationXInput->onTextInputEvent(this, &TransformMenu::onRotationXChanged);
	m_rotationYInput->onTextInputEvent(this, &TransformMenu::onRotationYChanged);
	m_rotationZInput->onTextInputEvent(this, &TransformMenu::onRotationZChanged);

	m_scaleXInput->onTextInputEvent(this, &TransformMenu::onScaleXChanged);
	m_scaleYInput->onTextInputEvent(this, &TransformMenu::onScaleYChanged);
	m_scaleZInput->onTextInputEvent(this, &TransformMenu::onScaleZChanged);
}

void TransformMenu::setEnabled(bool enabled) {
	m_positionXInput->setEnabled(enabled);
	m_positionYInput->setEnabled(enabled);
	m_positionZInput->setEnabled(enabled);
	m_scaleXInput->setEnabled(enabled);
	m_scaleYInput->setEnabled(enabled);
	m_scaleZInput->setEnabled(enabled);
	m_rotationXInput->setEnabled(enabled);
	m_rotationYInput->setEnabled(enabled);
	m_rotationZInput->setEnabled(enabled);
	if (!enabled) {
		m_positionXInput->setText("_");
		m_positionYInput->setText("_");
		m_positionZInput->setText("_");
		m_rotationXInput->setText("_");
		m_rotationYInput->setText("_");
		m_rotationZInput->setText("_");
		m_scaleXInput->setText("_");
		m_scaleYInput->setText("_");
		m_scaleZInput->setText("_");
	}
}

void TransformMenu::setup(int width, int height, int paddingX, int paddingY) {
	m_width = width;
	m_height = height;
	m_paddingX = paddingX;
	m_paddingY = paddingY;
	setupPositionInputs();
	setupRotationInputs();
	setupScaleInputs();


}

void TransformMenu::setupPositionInputs() {
	int inputWidth = (m_width - m_labelWidth - 5 * m_paddingX) / 3;
	m_positionLabel->setWidth(m_labelWidth);
	m_positionXInput->setWidth(inputWidth, .4);
	m_positionYInput->setWidth(inputWidth, .4);
	m_positionZInput->setWidth(inputWidth, .4);

	m_positionLabel->setPosition(m_paddingX, m_height);
	m_positionXInput->setPosition(m_positionLabel->getX() + m_positionLabel->getWidth() + m_paddingX, m_height);
	m_positionYInput->setPosition(m_positionXInput->getX() + m_positionXInput->getWidth() + m_paddingX, m_height);
	m_positionZInput->setPosition(m_positionYInput->getX() + m_positionYInput->getWidth() + m_paddingX, m_height);
}

void TransformMenu::setupRotationInputs() {
	int inputWidth = (m_width - m_labelWidth - 5 * m_paddingX) / 3;
	m_rotationLabel->setWidth(m_labelWidth);
	m_rotationXInput->setWidth(inputWidth, .4);
	m_rotationYInput->setWidth(inputWidth, .4);
	m_rotationZInput->setWidth(inputWidth, .4);

	int height = m_positionXInput->getY() + m_positionXInput->getHeight() + m_paddingY;
	m_rotationLabel->setPosition(m_paddingX, height);
	m_rotationXInput->setPosition(m_rotationLabel->getX() + m_rotationLabel->getWidth() + m_paddingX, height);
	m_rotationYInput->setPosition(m_rotationXInput->getX() + m_rotationXInput->getWidth() + m_paddingX, height);
	m_rotationZInput->setPosition(m_rotationYInput->getX() + m_rotationYInput->getWidth() + m_paddingX, height);
}

void TransformMenu::setupScaleInputs() {
	int inputWidth = (m_width - m_labelWidth - 5 * m_paddingX) / 3;
	m_scaleLabel->setWidth(m_labelWidth);
	m_scaleXInput->setWidth(inputWidth, .4);
	m_scaleYInput->setWidth(inputWidth, .4);
	m_scaleZInput->setWidth(inputWidth, .4);

	int height = m_rotationXInput->getY() + m_rotationXInput->getHeight() + m_paddingY;
	m_scaleLabel->setPosition(m_paddingX, height);
	m_scaleXInput->setPosition(m_scaleLabel->getX() + m_scaleLabel->getWidth() + m_paddingX, height);
	m_scaleYInput->setPosition(m_scaleXInput->getX() + m_scaleXInput->getWidth() + m_paddingX, height);
	m_scaleZInput->setPosition(m_scaleYInput->getX() + m_scaleYInput->getWidth() + m_paddingX, height);
}

void TransformMenu::setHeight(int height) {
	m_height = height;
}

void TransformMenu::mouseMoved(int x, int y) {
	m_lastMousePosition = ofPoint(x, y);
}

void TransformMenu::mousePressed(int x, int y, int button) {
	m_lastMousePosition = ofPoint(x, y);
	if (m_positionXInput->hitTest(ofPoint(x, y))) {
		m_positionXInputClicked = true;
		m_undoRedo.action(m_activeObjects);
	}
	else if (m_positionYInput->hitTest(ofPoint(x, y))) {
		m_positionYInputClicked = true;
		m_undoRedo.action(m_activeObjects);
	}
	else if (m_positionZInput->hitTest(ofPoint(x, y))) {
		m_positionZInputClicked = true;
		m_undoRedo.action(m_activeObjects);
	}
	else if (m_rotationXInput->hitTest(ofPoint(x, y))) {
		m_rotationXInputClicked = true;
		m_undoRedo.action(m_activeObjects);
	}
	else if (m_rotationYInput->hitTest(ofPoint(x, y))) {
		m_rotationYInputClicked = true;
		m_undoRedo.action(m_activeObjects);
	}
	else if (m_rotationZInput->hitTest(ofPoint(x, y))) {
		m_rotationZInputClicked = true;
		m_undoRedo.action(m_activeObjects);
	}
	else if (m_scaleXInput->hitTest(ofPoint(x, y))) {
		m_scaleXInputClicked = true;
		m_undoRedo.action(m_activeObjects);
	}
	else if (m_scaleYInput->hitTest(ofPoint(x, y))) {
		m_scaleYInputClicked = true;
		m_undoRedo.action(m_activeObjects);
	}
	else if (m_scaleZInput->hitTest(ofPoint(x, y))) {
		m_scaleZInputClicked = true;
		m_undoRedo.action(m_activeObjects);
	}
}

void TransformMenu::keyReleased(int key) {
	m_undoRedo.keyReleased(key);
}

void TransformMenu::setAllInputsUnfocusedExceptOne(ofxDatGuiTextInput* exception) {
	if (exception != m_positionXInput)
		m_positionXInput->setFocused(false);
	if (exception != m_positionYInput)
		m_positionYInput->setFocused(false);
	if (exception != m_positionZInput)
		m_positionZInput->setFocused(false);

	if (exception != m_rotationXInput)
		m_rotationXInput->setFocused(false);
	if (exception != m_rotationYInput)
		m_rotationYInput->setFocused(false);
	if (exception != m_rotationZInput)
		m_rotationZInput->setFocused(false);

	if (exception != m_scaleXInput)
		m_scaleXInput->setFocused(false);
	if (exception != m_scaleYInput)
		m_scaleYInput->setFocused(false);
	if (exception != m_scaleZInput)
		m_scaleZInput->setFocused(false);
}

void TransformMenu::mouseReleased(int x, int y, int button) {
	m_lastMousePosition = ofPoint(x, y);

	m_positionXInputClicked = false;
	m_positionYInputClicked = false;
	m_positionZInputClicked = false;

	m_rotationXInputClicked = false;
	m_rotationYInputClicked = false;
	m_rotationZInputClicked = false;

	m_scaleXInputClicked = false;
	m_scaleYInputClicked = false;
	m_scaleZInputClicked = false;
}

void TransformMenu::mouseDragged(int x, int y, int button) {
	if (m_activeObjects.size() == 0)
		return;

	float delta = (float)x - m_lastMousePosition.x;
	m_lastMousePosition = ofPoint(x, y);

	if (m_positionXInputClicked) {
		for (size_t i = 0; i < m_activeObjects.size(); i++) {
			m_activeObjects[i]->setPositionX(m_activeObjects[i]->getPosition().x + delta);
		}
		m_positionXInput->setText(formatFloatToText(m_activeObjects[0]->getPosition().x));
		setAllInputsUnfocusedExceptOne(m_positionXInput);
	}
	else if (m_positionYInputClicked) {
		for (size_t i = 0; i < m_activeObjects.size(); i++) {
			m_activeObjects[i]->setPositionY(m_activeObjects[i]->getPosition().y + delta);
		}
		m_positionYInput->setText(formatFloatToText(m_activeObjects[0]->getPosition().y));
		setAllInputsUnfocusedExceptOne(m_positionYInput);
	}
	else if (m_positionZInputClicked) {
		for (size_t i = 0; i < m_activeObjects.size(); i++) {
			m_activeObjects[i]->setPositionZ(m_activeObjects[i]->getPosition().z + delta);
		}
		m_positionZInput->setText(formatFloatToText(m_activeObjects[0]->getPosition().z));
		setAllInputsUnfocusedExceptOne(m_positionZInput);
	}
	else if (m_rotationXInputClicked) {
		for (size_t i = 0; i < m_activeObjects.size(); i++) {
			m_activeObjects[i]->addRotationX(delta);
		}
		m_rotationXInput->setText(formatFloatToText(m_activeObjects[0]->getRotation().x));
		setAllInputsUnfocusedExceptOne(m_rotationXInput);
	}
	else if (m_rotationYInputClicked) {
		for (size_t i = 0; i < m_activeObjects.size(); i++) {
			m_activeObjects[i]->addRotationY(delta);
		}
		m_rotationYInput->setText(formatFloatToText(m_activeObjects[0]->getRotation().y));
		setAllInputsUnfocusedExceptOne(m_rotationYInput);
	}
	else if (m_rotationZInputClicked) {
		for (size_t i = 0; i < m_activeObjects.size(); i++) {
			m_activeObjects[i]->addRotationZ(delta);
		}
		m_rotationZInput->setText(formatFloatToText(m_activeObjects[0]->getRotation().z));
		setAllInputsUnfocusedExceptOne(m_rotationZInput);
	}
	else if (m_scaleXInputClicked) {
		for (size_t i = 0; i < m_activeObjects.size(); i++) {
			m_activeObjects[i]->setScaleX(m_activeObjects[i]->getScale().x + (float)delta * 0.01f);
		}
		m_scaleXInput->setText(formatFloatToText(m_activeObjects[0]->getScale().x));
		setAllInputsUnfocusedExceptOne(m_scaleXInput);
	}
	else if (m_scaleYInputClicked) {
		for (size_t i = 0; i < m_activeObjects.size(); i++) {
			m_activeObjects[i]->setScaleY(m_activeObjects[i]->getScale().y + (float)delta * 0.01f);
		}
		m_scaleYInput->setText(formatFloatToText(m_activeObjects[0]->getScale().y));
		setAllInputsUnfocusedExceptOne(m_scaleYInput);
	}
	else if (m_scaleZInputClicked) {
		for (size_t i = 0; i < m_activeObjects.size(); i++) {
			m_activeObjects[i]->setScaleZ(m_activeObjects[i]->getScale().z + (float)delta * 0.01f);
		}
		m_scaleZInput->setText(formatFloatToText(m_activeObjects[0]->getScale().z));
		setAllInputsUnfocusedExceptOne(m_scaleZInput);
	}
}

void TransformMenu::setActiveObject(const std::vector<Object*>& activeObjects) {
	m_activeObjects = activeObjects;

	if (m_activeObjects.size() == 0)
		return;

	m_positionXInput->setText(formatFloatToText(m_activeObjects[0]->getPosition().x));
	m_positionYInput->setText(formatFloatToText(m_activeObjects[0]->getPosition().y));
	m_positionZInput->setText(formatFloatToText(m_activeObjects[0]->getPosition().z));

	m_rotationXInput->setText(formatFloatToText(m_activeObjects[0]->getRotation().x));
	m_rotationYInput->setText(formatFloatToText(m_activeObjects[0]->getRotation().y));
	m_rotationZInput->setText(formatFloatToText(m_activeObjects[0]->getRotation().z));

	m_scaleXInput->setText(formatFloatToText(m_activeObjects[0]->getScale().x));
	m_scaleYInput->setText(formatFloatToText(m_activeObjects[0]->getScale().y));
	m_scaleZInput->setText(formatFloatToText(m_activeObjects[0]->getScale().z));
}

ofVec2f TransformMenu::getBottomCoord() const {
	ofVec2f result;
	result.x = m_scaleXInput->getX() + m_scaleXInput->getWidth();
	result.y = m_scaleXInput->getY() + m_scaleXInput->getHeight();
	return result;
}

void TransformMenu::moveActiveObjects() {
	if (moveObjects == false) {
		m_lastMousePosition = ofPoint(ofGetMouseX(), ofGetMouseY());
		moveObjects = true;
		m_undoRedo.action(m_activeObjects);
	}
	float deltaX = (float)ofGetMouseX() - m_lastMousePosition.x;
	float deltaY = (float)ofGetMouseY() - m_lastMousePosition.y;
	m_lastMousePosition = ofPoint(ofGetMouseX(), ofGetMouseY());

	glm::vec3 delta1 = m_camera->getLeft() * deltaX;
	glm::vec3 delta2 = m_camera->getUp() * -deltaY;

	for (size_t i = 0; i < m_activeObjects.size(); i++) {
		if (m_activeObjects[i]->isVectorGraphics()) {
			m_activeObjects[i]->setPositionX(m_activeObjects[i]->getPosition().x + deltaX);
			m_activeObjects[i]->setPositionY(m_activeObjects[i]->getPosition().y + deltaY);
		}
		else {
			m_activeObjects[i]->translate(delta1 + delta2);
		}
	}
	if (!m_activeObjects.empty()) {
		m_positionXInput->setText(formatFloatToText(m_activeObjects[0]->getPosition().x));
		m_positionYInput->setText(formatFloatToText(m_activeObjects[0]->getPosition().y));
	}
}

void TransformMenu::scaleActiveObjects() {
	if (scaleObjects == false) {
		m_lastMousePositionForScaling = ofPoint(ofGetMouseX(), ofGetMouseY());
		scaleObjects = true;
		m_undoRedo.action(m_activeObjects);
	}
	int deltaX = ofGetMouseX() - m_lastMousePositionForScaling.x;
	int deltaY = m_lastMousePositionForScaling.y - ofGetMouseY();
	float mulFactor = 1 + ((float)deltaX + (float)deltaY) / 700.0f;
	m_lastMousePositionForScaling = ofPoint(ofGetMouseX(), ofGetMouseY());

	for (size_t i = 0; i < m_activeObjects.size(); i++) {
		glm::vec3 newScale = m_activeObjects[i]->getScale() * mulFactor;
		m_activeObjects[i]->setScale(newScale.x, newScale.y, newScale.z);
	}
	if (!m_activeObjects.empty()) {
		m_scaleXInput->setText(formatFloatToText(m_activeObjects[0]->getScale().x));
		m_scaleYInput->setText(formatFloatToText(m_activeObjects[0]->getScale().y));
		m_scaleZInput->setText(formatFloatToText(m_activeObjects[0]->getScale().z));
	}
}

void TransformMenu::rotateXActiveObjects() {
	if (rotateXObjects == false) {
		m_lastMousePositionForScaling = ofPoint(ofGetMouseX(), ofGetMouseY());
		rotateXObjects = true;
		m_undoRedo.action(m_activeObjects);
	}
	int deltaX = ofGetMouseX() - m_lastMousePositionForScaling.x;
	int deltaY = m_lastMousePositionForScaling.y - ofGetMouseY();
	float delta = ((float)deltaX + (float)deltaY) / 10.0f;
	m_lastMousePositionForScaling = ofPoint(ofGetMouseX(), ofGetMouseY());

	for (size_t i = 0; i < m_activeObjects.size(); i++) {
		m_activeObjects[i]->addRotationX(delta);
	}
	if (!m_activeObjects.empty()) {
		m_rotationXInput->setText(formatFloatToText(m_activeObjects[0]->getRotation().x));
	}
}

void TransformMenu::rotateYActiveObjects() {
	if (rotateYObjects == false) {
		m_lastMousePositionForScaling = ofPoint(ofGetMouseX(), ofGetMouseY());
		rotateYObjects = true;
		m_undoRedo.action(m_activeObjects);
	}
	int deltaX = ofGetMouseX() - m_lastMousePositionForScaling.x;
	int deltaY = m_lastMousePositionForScaling.y - ofGetMouseY();
	float delta = ((float)deltaX + (float)deltaY) / 10.0f;
	m_lastMousePositionForScaling = ofPoint(ofGetMouseX(), ofGetMouseY());

	for (size_t i = 0; i < m_activeObjects.size(); i++) {
		m_activeObjects[i]->addRotationY(delta);
	}
	if (!m_activeObjects.empty()) {
		m_rotationYInput->setText(formatFloatToText(m_activeObjects[0]->getRotation().y));
	}
}

void TransformMenu::rotateZActiveObjects() {
	if (rotateZObjects == false) {
		m_lastMousePositionForScaling = ofPoint(ofGetMouseX(), ofGetMouseY());
		rotateZObjects = true;
		m_undoRedo.action(m_activeObjects);
	}
	int deltaX = ofGetMouseX() - m_lastMousePositionForScaling.x;
	int deltaY = m_lastMousePositionForScaling.y - ofGetMouseY();
	float delta = ((float)deltaX + (float)deltaY) / 10.0f;
	m_lastMousePositionForScaling = ofPoint(ofGetMouseX(), ofGetMouseY());

	for (size_t i = 0; i < m_activeObjects.size(); i++) {
		m_activeObjects[i]->addRotationZ(delta);
	}
	if (!m_activeObjects.empty()) {
		m_rotationZInput->setText(formatFloatToText(m_activeObjects[0]->getRotation().z));
	}
}

void TransformMenu::setEverythingFocused(bool focused) {
	m_positionXInput->setFocused(focused);
	m_positionYInput->setFocused(focused);
	m_positionZInput->setFocused(focused);
	m_rotationXInput->setFocused(focused);
	m_rotationYInput->setFocused(focused);
	m_rotationZInput->setFocused(focused);
	m_scaleXInput->setFocused(focused);
	m_scaleYInput->setFocused(focused);
	m_scaleZInput->setFocused(focused);
}

void TransformMenu::update() {
	if (InputController::isKeyDown(KEY::G)) {
		moveActiveObjects();
		setEverythingFocused(false);
	}
	else {
		moveObjects = false;
	}

	if (InputController::isKeyDown(KEY::S)) {
		scaleActiveObjects();
		setEverythingFocused(false);
	}
	else {
		scaleObjects = false;
	}

	if (InputController::isKeyDown(KEY::R) && InputController::isKeyDown(KEY::X)) {
		rotateXActiveObjects();
		setEverythingFocused(false);
	}
	else {
		rotateXObjects = false;
	}
	if (InputController::isKeyDown(KEY::R) && InputController::isKeyDown(KEY::Y)) {
		rotateYActiveObjects();
		setEverythingFocused(false);
	}
	else {
		rotateYObjects = false;
	}
	if (InputController::isKeyDown(KEY::R) && InputController::isKeyDown(KEY::Z)) {
		rotateZActiveObjects();
		setEverythingFocused(false);
	}
	else {
		rotateZObjects = false;
	}
	if (!m_activeObjects.empty()) {
		if(!m_positionXInput->getFocused())
			m_positionXInput->setText(formatFloatToText(m_activeObjects[0]->getPosition().x));
		if (!m_positionYInput->getFocused())
			m_positionYInput->setText(formatFloatToText(m_activeObjects[0]->getPosition().y));
		if (!m_positionZInput->getFocused())
			m_positionZInput->setText(formatFloatToText(m_activeObjects[0]->getPosition().z));

		if (!m_scaleXInput->getFocused())
			m_scaleXInput->setText(formatFloatToText(m_activeObjects[0]->getScale().x));
		if (!m_scaleYInput->getFocused())
			m_scaleYInput->setText(formatFloatToText(m_activeObjects[0]->getScale().y));
		if (!m_scaleZInput->getFocused())
			m_scaleZInput->setText(formatFloatToText(m_activeObjects[0]->getScale().z));

		if (!m_rotationXInput->getFocused())
			m_rotationXInput->setText(formatFloatToText(m_activeObjects[0]->getRotation().x));
		if (!m_rotationYInput->getFocused())
			m_rotationYInput->setText(formatFloatToText(m_activeObjects[0]->getRotation().y));
		if (!m_rotationZInput->getFocused())
			m_rotationZInput->setText(formatFloatToText(m_activeObjects[0]->getRotation().z));
	}

	m_positionLabel->update();
	m_positionXInput->update();
	m_positionYInput->update();
	m_positionZInput->update();

	m_rotationLabel->update();
	m_rotationXInput->update();
	m_rotationYInput->update();
	m_rotationZInput->update();

	m_scaleLabel->update();
	m_scaleXInput->update();
	m_scaleYInput->update();
	m_scaleZInput->update();
}

void TransformMenu::draw() {
	m_positionLabel->draw();
	m_positionXInput->draw();
	m_positionYInput->draw();
	m_positionZInput->draw();

	m_rotationLabel->draw();
	m_rotationXInput->draw();
	m_rotationYInput->draw();
	m_rotationZInput->draw();

	m_scaleLabel->draw();
	m_scaleXInput->draw();
	m_scaleYInput->draw();
	m_scaleZInput->draw();
}

void TransformMenu::onPositionXChanged(ofxDatGuiTextInputEvent e) {
	if (m_activeObjects.empty())
		return;
	if (!validFloat(e.text) || (!InputController::isKeyDown(KEY::ENTER) && !InputController::isKeyDown(KEY::TAB))) {
		m_positionXInput->setText(formatFloatToText(m_activeObjects[0]->getPosition().x));
		return;
	}
	m_undoRedo.action(m_activeObjects);
	for (size_t i = 0; i < m_activeObjects.size(); i++) {
		m_activeObjects[i]->setPositionX(formatTextToFloat(e.text));
	}
	m_positionXInput->setText(formatFloatToText(m_activeObjects[0]->getPosition().x));
}

void TransformMenu::onPositionYChanged(ofxDatGuiTextInputEvent e) {
	if (m_activeObjects.empty())
		return;
	if (!validFloat(e.text) || (!InputController::isKeyDown(KEY::ENTER) && !InputController::isKeyDown(KEY::TAB))) {
		m_positionYInput->setText(formatFloatToText(m_activeObjects[0]->getPosition().y));
		return;
	}
	m_undoRedo.action(m_activeObjects);
	for (size_t i = 0; i < m_activeObjects.size(); i++) {
		m_activeObjects[i]->setPositionY(formatTextToFloat(e.text));
	}
	m_positionYInput->setText(formatFloatToText(m_activeObjects[0]->getPosition().y));
}
void TransformMenu::onPositionZChanged(ofxDatGuiTextInputEvent e) {
	if (m_activeObjects.empty())
		return;
	if (!validFloat(e.text) || (!InputController::isKeyDown(KEY::ENTER) && !InputController::isKeyDown(KEY::TAB))) {
		m_positionZInput->setText(formatFloatToText(m_activeObjects[0]->getPosition().z));
		return;
	}
	m_undoRedo.action(m_activeObjects);
	for (size_t i = 0; i < m_activeObjects.size(); i++) {
		m_activeObjects[i]->setPositionZ(formatTextToFloat(e.text));
	}
	m_positionZInput->setText(formatFloatToText(m_activeObjects[0]->getPosition().z));
}

void TransformMenu::onRotationXChanged(ofxDatGuiTextInputEvent e) {
	if (m_activeObjects.empty())
		return;
	if (!validFloat(e.text) || (!InputController::isKeyDown(KEY::ENTER) && !InputController::isKeyDown(KEY::TAB))) {
		m_rotationXInput->setText(formatFloatToText(m_activeObjects[0]->getRotation().x));
		return;
	}
	m_undoRedo.action(m_activeObjects);
	for (size_t i = 0; i < m_activeObjects.size(); i++) {
		m_activeObjects[i]->setRotationX(formatTextToFloat(e.text));
	}
	m_rotationXInput->setText(e.text);
}

void TransformMenu::onRotationYChanged(ofxDatGuiTextInputEvent e) {
	if (m_activeObjects.empty())
		return;
	if (!validFloat(e.text) || (!InputController::isKeyDown(KEY::ENTER) && !InputController::isKeyDown(KEY::TAB))) {
		m_rotationXInput->setText(formatFloatToText(m_activeObjects[0]->getRotation().y));
		return;
	}
	m_undoRedo.action(m_activeObjects);
	for (size_t i = 0; i < m_activeObjects.size(); i++) {
		m_activeObjects[i]->setRotationY(formatTextToFloat(e.text));
	}
	m_rotationYInput->setText(e.text);
}
void TransformMenu::onRotationZChanged(ofxDatGuiTextInputEvent e) {
	if (m_activeObjects.empty())
		return;
	if (!validFloat(e.text) || (!InputController::isKeyDown(KEY::ENTER) && !InputController::isKeyDown(KEY::TAB))) {
		m_rotationXInput->setText(formatFloatToText(m_activeObjects[0]->getRotation().z));
		return;
	}
	m_undoRedo.action(m_activeObjects);
	for (size_t i = 0; i < m_activeObjects.size(); i++) {
		m_activeObjects[i]->setRotationZ(formatTextToFloat(e.text));
	}
	m_rotationZInput->setText(e.text);
}

void TransformMenu::onScaleXChanged(ofxDatGuiTextInputEvent e) {
	if (m_activeObjects.empty())
		return;
	if (!validFloat(e.text) || (!InputController::isKeyDown(KEY::ENTER) && !InputController::isKeyDown(KEY::TAB))) {
		m_scaleXInput->setText(formatFloatToText(m_activeObjects[0]->getScale().x));
		return;
	}
	m_undoRedo.action(m_activeObjects);
	for (size_t i = 0; i < m_activeObjects.size(); i++) {
		m_activeObjects[i]->setScaleX(formatTextToFloat(e.text));
	}
	m_scaleXInput->setText(formatFloatToText(m_activeObjects[0]->getScale().x));
}

void TransformMenu::onScaleYChanged(ofxDatGuiTextInputEvent e) {
	if (m_activeObjects.empty())
		return;
	if (!validFloat(e.text) || (!InputController::isKeyDown(KEY::ENTER) && !InputController::isKeyDown(KEY::TAB))) {
		m_scaleXInput->setText(formatFloatToText(m_activeObjects[0]->getScale().y));
		return;
	}
	m_undoRedo.action(m_activeObjects);
	for (size_t i = 0; i < m_activeObjects.size(); i++) {
		m_activeObjects[i]->setScaleY(formatTextToFloat(e.text));
	}
	m_scaleYInput->setText(formatFloatToText(m_activeObjects[0]->getScale().y));
}
void TransformMenu::onScaleZChanged(ofxDatGuiTextInputEvent e) {
	if (m_activeObjects.empty())
		return;
	if (!validFloat(e.text) || (!InputController::isKeyDown(KEY::ENTER) && !InputController::isKeyDown(KEY::TAB))) {
		m_scaleZInput->setText(formatFloatToText(m_activeObjects[0]->getScale().z));
		return;
	}
	m_undoRedo.action(m_activeObjects);
	for (size_t i = 0; i < m_activeObjects.size(); i++) {
		m_activeObjects[i]->setScaleZ(formatTextToFloat(e.text));
	}
	m_scaleZInput->setText(formatFloatToText(m_activeObjects[0]->getScale().z));
}

std::string TransformMenu::formatFloatToText(float number) {
	std::string result = std::to_string(number);
	std::size_t pos = result.find(".");
	return result.substr(0, pos + 3);
}

float TransformMenu::formatTextToFloat(const std::string& text) {
	try {
		float result = std::stof(text);
		return result;
	}
	catch (const std::exception& e) {
		return 0.0f;
	}
}

bool TransformMenu::validFloat(const std::string& text) {
	try {
		float result = std::stof(text);
		return true;
	}
	catch (const std::exception& e) {
		return false;
	}
}

TransformMenu::~TransformMenu() {
	delete m_positionLabel;
	delete m_positionXInput;
	delete m_positionYInput;
	delete m_positionZInput;

	delete m_rotationLabel;
	delete m_rotationXInput;
	delete m_rotationYInput;
	delete m_rotationZInput;

	delete m_scaleLabel;
	delete m_scaleXInput;
	delete m_scaleYInput;
	delete m_scaleZInput;
}