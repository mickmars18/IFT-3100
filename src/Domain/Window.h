#pragma once

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

class Window {
public:
	void setDimensions(int x, int y, int width, int height);
	int getX() const { return m_x; }
	int getY() const { return m_y; };
	int getWidth() const { return m_width; };
	int getHeight() const { return m_height; };

	bool isInWindow(int x, int y) const;

	glm::mat4 getOrigin() const;
private:
	int m_x;
	int m_y;
	int m_width;
	int m_height;
};
