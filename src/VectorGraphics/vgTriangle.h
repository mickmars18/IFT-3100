#pragma once
#include "../Domain/Object.h"

class vgTriangle : public Object {
public:
	vgTriangle(int x, int y, ofPoint dimension, const ofColor& color, int lineWidth, const ofColor& lineColor);
	std::string getClassName() override;
	void update() override;
	void draw(const Window& window, const Camera& camera) override;
	void changeColor(const ofColor& color) override;
	inline ofPoint getDimension() const { return m_dimension; }
	inline void setDimension(ofPoint dimension) { m_dimension = dimension; }
	bool hasColorAttribute() override { return true; }
	ofColor getColor() const override { return m_color; }
	inline int getLineWidth() const { return m_lineWidth; }
	inline void setLineWidth(int lineWidth) { m_lineWidth = lineWidth; }
	virtual bool isVectorGraphics() const { return true; }
private:
	ofPoint m_dimension;
	int m_lineWidth = 2;
	ofColor m_color;
	ofColor m_lineColor;
};
