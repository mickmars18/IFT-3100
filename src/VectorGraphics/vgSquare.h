#pragma once
#include "../Domain/Object.h"

class vgSquare : public Object {
public:
	vgSquare(int x, int y, int width, const ofColor& color, int lineWidth, const ofColor& lineColor);
	std::string getClassName() override;
	void update() override;
	void draw(const Window& window, const Camera& camera) override;
	void changeColor(const ofColor& color) override;
	inline int getDimension() const { return m_width; }
	inline void setDimension(int width) { m_width = width; }
	bool hasColorAttribute() override { return true; }
	ofColor getColor() const override { return m_color; }
	inline int getLineWidth() const { return m_lineWidth; }
	inline void setLineWidth(int lineWidth) { m_lineWidth = lineWidth; }
	virtual bool isVectorGraphics() const { return true; }
private:
	int m_width;
	int m_lineWidth = 2;
	ofColor m_color;
	ofColor m_lineColor;
};