#pragma once
#include "../Domain/Object.h"

class vgCircle : public Object {
public:
	vgCircle(int x, int y, int radius, const ofColor& color, int lineWidth, const ofColor& lineColor);
	std::string getClassName() override;
	void update() override;
	void draw(const Window& window, const Camera& camera) override;
	void changeColor(const ofColor& color) override;
	inline int getRadius() const { return m_radius; }
	inline void setRadius(int radius) { m_radius = radius; }
	bool hasColorAttribute() override { return true; }
	ofColor getColor() const override { return m_color; }
	inline int getLineWidth() const { return m_lineWidth; }
	inline void setLineWidth(int lineWidth) { m_lineWidth = lineWidth; }
	virtual bool isVectorGraphics() const { return true; }
private:
	int m_radius;
	int m_lineWidth = 2;
	ofColor m_color;
	ofColor m_lineColor;
};
