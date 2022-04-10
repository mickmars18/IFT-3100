#pragma once
#include "Tools/InputController.h"

class CameraController {
public:
	inline void setCamera(Camera* camera) { m_camera = camera; }
	inline void middleMouseDraged(ofVec2f movement) {
		m_camera->moveLeft(movement.x);
		m_camera->moveUp(movement.y);
	}
	inline void rightMouseDraged(ofVec2f movement) {
		m_camera->rotateUpAxis(ofDegToRad(-movement.x) * m_rotatingSpeed);
		m_camera->rotateLeftAxis(ofDegToRad(-movement.y) * m_rotatingSpeed);
	}
	inline void zoom(float value) {
		m_camera->moveForward(value * m_zoomSpeed);
	}
	inline void mouseReleased(int button) {
		float currentTime = ofGetElapsedTimef();
		float delta = currentTime - m_lastTime;
		m_lastTime = ofGetElapsedTimef();
		if (button == OF_MOUSE_BUTTON_3 && delta < 0.5f) {
			m_camera->resetUp();
		}
	}
private:
	Camera* m_camera;
	float m_zoomSpeed = 50.0f;
	float m_rotatingSpeed = 0.1f;
	float m_lastTime = ofGetElapsedTimef();
};
