#include "Window.h"

void Window::setDimensions(int x, int y, int width, int height) {
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
}

glm::mat4 Window::getOrigin() const {
	return glm::translate(glm::vec3(m_x, m_y, 0.0f));
}

bool Window::isInWindow(int x, int y) const {
	if (x >= m_x && x <= m_x + m_width && y >= m_y && y <= m_y + m_height)
		return true;
	else
		return false;
}