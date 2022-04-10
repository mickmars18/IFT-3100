#pragma once
#include "VectorGraphics.h"
#include "../Domain/Window.h"
#include "../Domain/Object.h"
#include "../Tools/InputController.h"
#include "../Menu/Themes.h"
#include <memory>

enum class PrimitiveType {
	Circle,
	Ellipse,
	Square,
	Rectangle,
	Triangle,
	StripedCircles,
	GeometricPattern
};

class VectorGraphicsInitializer {
public:
	VectorGraphicsInitializer();
	void mouseDragged(int x, int y, int button);
	Object* mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void keyPressed(int key);
	void drawStatus(const Window& window);

	bool isVectorDrawingMode() const { return m_vectorGraphicsDrawingMode; }
	void disableDrawingMode();
	std::string getDrawingType();

	int getLineWidth() const { return m_lineWidth; }
	void setLineWidth(int lineWidth);

	ofColor getFillColor() const { return m_fillColor; }
	void setFillColor(const ofColor& color) { m_fillColor = color; }

	ofColor getLineColor() const { return m_lineColor; }
	void setLineColor(const ofColor& color) { m_lineColor = color; }
private:
	Object* m_newObject = nullptr;
	ofPoint m_initialPointClick;

	bool m_vectorGraphicsDrawingMode = false;
	bool m_drawing = false;
	PrimitiveType m_primitiveTypeToDraw = PrimitiveType::GeometricPattern;
	void setNextPrimitiveType();

	ofTrueTypeFont m_font;
	int m_lineWidth = 2;
	ofColor m_fillColor = ofColor::white;
	ofColor m_lineColor = ofColor::black;
};
