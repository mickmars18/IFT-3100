#include "Cursor.h"

Cursor::Cursor() {
	m_moveCursor = new ofImage("cursors/moveCursor.png");
	m_scaleCursor = new ofImage("cursors/scaleCursor.png");
	m_rotateXCursor = new ofImage("cursors/rotateXCursor.png");
	m_rotateYCursor = new ofImage("cursors/rotateYCursor.png");
	m_rotateZCursor = new ofImage("cursors/rotateZCursor.png");

	m_rotateXCursor->resize(32, 32);
	m_rotateYCursor->resize(32, 32);
	m_rotateZCursor->resize(32, 32);
}

void Cursor::update() {
	if (InputController::isKeyDown(KEY::G)) {
		showCursor(m_showMoveCursor);
		return;
	}
	else if (InputController::isKeyDown(KEY::S)) {
		showCursor(m_showScaleCursor);
		return;
	}
	else if (InputController::isKeyDown(KEY::R) && InputController::isKeyDown(KEY::X)) {
		showCursor(m_showRotateXCursor);
		return;
	}
	else if (InputController::isKeyDown(KEY::R) && InputController::isKeyDown(KEY::Y)) {
		showCursor(m_showRotateYCursor);
		return;
	}
	else if (InputController::isKeyDown(KEY::R) && InputController::isKeyDown(KEY::Z)) {
		showCursor(m_showRotateZCursor);
		return;
	}
	else {
		m_showMoveCursor = false;
		m_showScaleCursor = false;
		m_showRotateXCursor = false;
		m_showRotateYCursor = false;
		m_showRotateZCursor = false;
	}
}

void Cursor::showCursor(bool& cursorToShow) {
	m_showMoveCursor = false;
	m_showScaleCursor = false;
	m_showRotateXCursor = false;
	m_showRotateYCursor = false;
	m_showRotateZCursor = false;
	cursorToShow = true;
}

void Cursor::draw() {
	if (!m_showMoveCursor && !m_showScaleCursor && !m_showRotateXCursor && !m_showRotateYCursor && !m_showRotateZCursor) {
		ofShowCursor();
		return;
	}

	ofHideCursor();
	ofEnableAlphaBlending();
	ofSetColor(255, 255, 255, 200);

	if (m_showMoveCursor) {
		m_moveCursor->draw(ofGetMouseX(), ofGetMouseY(), m_moveCursor->getWidth(), m_moveCursor->getHeight());
	}
	if (m_showScaleCursor) {
		m_scaleCursor->draw(ofGetMouseX(), ofGetMouseY(), m_moveCursor->getWidth(), m_moveCursor->getHeight());
	}
	if (m_showRotateXCursor) {
		m_rotateXCursor->draw(ofGetMouseX(), ofGetMouseY(), m_moveCursor->getWidth(), m_moveCursor->getHeight());
	}
	if (m_showRotateYCursor) {
		m_rotateYCursor->draw(ofGetMouseX(), ofGetMouseY(), m_moveCursor->getWidth(), m_moveCursor->getHeight());
	}
	if (m_showRotateZCursor) {
		m_rotateZCursor->draw(ofGetMouseX(), ofGetMouseY(), m_moveCursor->getWidth(), m_moveCursor->getHeight());
	}
	ofDisableAlphaBlending();
}

Cursor::~Cursor() {
	ofShowCursor();
	delete m_moveCursor;
	delete m_scaleCursor;
}