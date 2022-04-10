#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "Window.h"
#include "ofAppRunner.h"

class Camera {
public:

	Camera(Window* window) :
		m_fov(60.0f)
	{
		m_window = window;
		setInitialPosition();
	}

	void setWindow(Window* window) { m_window = window; }

	void setInitialPosition() {
		m_position = m_initialPosition;
		m_forward = glm::vec3(0, 0, -1);
		m_up = glm::vec3(0, 1, 0);
	}

	void resetUp() {
		m_up = glm::vec3(0, 1, 0);
	}

	bool isOrtho() const { return m_isOrtho; }

	void enableOrtho() {
		if (!m_isOrtho) {
			m_isOrtho = true;
		}
	}

	void disableOrtho() {
		if (m_isOrtho) {
			m_isOrtho = false;
		}
	}

	inline void lookAt(const glm::vec3& position) {
		setPosition(position - m_forward * 300.0f);
	}

	inline void setPosition(const glm::vec3& position) { m_position = position; }

	inline glm::vec3 getPosition() const { return m_position; }

	inline void moveLeft(float value) { 
		m_position -= glm::cross(m_forward, m_up) * value;
	}
	inline void moveRight(float value) {
		m_position += glm::cross(m_forward, m_up) * value;
	}
	inline void moveForward(float value) {
		m_position += m_forward * value;
		m_orthoZoom -= value * m_orthoSpeed;
		m_orthoZoom = CLAMP(m_orthoZoom, 0.1f, 100.0f);
	}
	inline void moveBackward(float value) {
		m_position -= m_forward * value;
		m_orthoZoom += value * m_orthoSpeed;
		m_orthoZoom = CLAMP(m_orthoZoom, 0.1f, 100.0f);
	}
	inline void moveUp(float value) { m_position += m_up * value; }
	inline void moveDown(float value) { m_position -= m_up * value; }

	inline void rotateLeftAxis(float degree) {
		glm::vec3 leftAxis = glm::cross(m_forward, m_up);
		m_forward = glm::rotate(m_forward, degree, leftAxis);
		m_up = glm::rotate(m_up, degree, leftAxis);
	}
	inline void rotateUpAxis(float degree) {
		m_forward = glm::rotate(m_forward, degree, m_up);
	}
	inline void rotateForwardAxis(float degree) {
		m_up = glm::rotate(m_up, degree, m_forward);
	}

	inline glm::mat4 getProjection() const {
		if (!m_isOrtho) {
			float aspect = (float)m_window->getWidth() / (float)m_window->getHeight();
			return glm::perspective(glm::radians(m_fov), aspect, m_nearClip, m_farClip);
		}
		else {
			return glm::ortho(-m_window->getWidth() / 2.0f * m_orthoZoom,
				m_window->getWidth() / 2.0f * m_orthoZoom,
				-m_window->getHeight() / 2.0f * m_orthoZoom,
				m_window->getHeight() / 2.0f * m_orthoZoom,
				m_nearClip, m_farClip);
		}
	}

	inline glm::mat4 getOrtho() const {
		return glm::ortho(-m_window->getWidth() / 2.0f * m_orthoZoom,
			m_window->getWidth() / 2.0f * m_orthoZoom,
			-m_window->getHeight() / 2.0f * m_orthoZoom,
			m_window->getHeight() / 2.0f * m_orthoZoom,
			m_nearClip, m_farClip);
	}

	inline glm::mat4 getViewMatrix() const {
		return glm::lookAt(m_position, m_position + m_forward, m_up); 
	}

	inline glm::vec3 getForward() const { return m_forward; }
	inline glm::vec3 getUp() const { return m_up; }
	inline glm::vec3 getLeft() const { return glm::cross(m_forward, m_up); }

private:
	Window* m_window;
	glm::vec3 m_position;
	glm::vec3 m_forward;
	glm::vec3 m_up;
	float m_nearClip = 1.0f;
	float m_farClip = 10000.0f;
	float m_fov;

	bool m_isOrtho = false;
	float m_orthoZoom = 1.0f;
	float m_orthoSpeed = 1.0f / 1000.0f;
	glm::vec3 m_initialPosition = glm::vec3(0, 200, 935);
};
