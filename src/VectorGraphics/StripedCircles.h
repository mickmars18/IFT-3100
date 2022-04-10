#pragma once
#include "../Domain/Object.h"

class StripedCircle : public Object {
public:
	StripedCircle(int x, int y, int radius, const ofColor& color1, const ofColor& color2, int nbStrips);
	void reset();
	std::string getClassName() override;
	void update() override;
	void draw(const Window& window, const Camera& camera) override;
	inline int getRadius() const { return m_radius; }
	inline void setRadius(int radius) { m_radius = radius; }
	virtual bool isVectorGraphics() const { return true; }
private:
	int m_radius;
	int m_nbStrips;
	ofColor m_color1;
	ofColor m_color2;
};
