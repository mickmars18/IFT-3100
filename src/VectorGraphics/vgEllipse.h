#pragma once
#include "../Domain/Object.h"

class vgEllipse : public Object {
public:
	vgEllipse(int x, int y, ofPoint radius, const ofColor& color, int lineWidth, const ofColor& lineColor);
	std::string getClassName() override;
	void update() override;
	void draw(const Window& window, const Camera& camera) override;
	void changeColor(const ofColor& color) override;
	inline ofPoint getRadius() const { return m_radius; }
	inline void setRadius(const ofPoint& radius) { m_radius = radius; }
	bool hasColorAttribute() override { return true; }
	ofColor getColor() const override { return m_color; }
	inline int getLineWidth() const { return m_lineWidth; }
	inline void setLineWidth(int lineWidth) { m_lineWidth = lineWidth; }
	virtual bool isVectorGraphics() const { return true; }
private:
	ofPoint m_radius;
	int m_lineWidth = 2;
	ofColor m_color;
	ofColor m_lineColor;
};
