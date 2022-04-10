#pragma once
#include "../Domain/Object.h"

class vgRectangle : public Object {
public:
	vgRectangle(int x, int y, ofPoint dimension, const ofColor& color, int lineWidth, const ofColor& lineColor);
	std::string getClassName() override;
	void update() override;
	void draw(const Window& window, const Camera& camera) override;
	void changeColor(const ofColor& color) override;
	inline ofPoint getDimension() const { return m_dimension; }
	inline void setDimension(const ofPoint& radius) { m_dimension = radius; }
	bool hasColorAttribute() override { return true; }
	ofColor getColor() const override { return m_color; }
	virtual bool isVectorGraphics() const { return true; }
private:
	ofPoint m_dimension;
	int m_lineWidth;
	ofColor m_color;
	ofColor m_lineColor;
};
