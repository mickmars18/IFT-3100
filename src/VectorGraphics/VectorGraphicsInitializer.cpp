#include "VectorGraphicsInitializer.h"

VectorGraphicsInitializer::VectorGraphicsInitializer() {
	m_font.load(Themes::getFontName(), 12);
}

void VectorGraphicsInitializer::mouseDragged(int x, int y, int button) {
	if (m_newObject == nullptr) {
		return;
	}

	int newX;
	int newY;
		
	switch (m_primitiveTypeToDraw) {
		case PrimitiveType::Circle:
			newX = 2 * (x - m_initialPointClick.x);
			newY = 2 * (y - m_initialPointClick.y);
			newX = sqrt(newX * newX + newY * newY);
			dynamic_cast<vgCircle*>(m_newObject)->setRadius(newX);
			break;
		case PrimitiveType::Ellipse:
			newX = 2 * (x - m_initialPointClick.x);
			newY = 2 * (y - m_initialPointClick.y);
			dynamic_cast<vgEllipse*>(m_newObject)->setRadius(ofPoint(newX, newY));
			break;
		case PrimitiveType::Square:
			newX = (x - m_initialPointClick.x) + 20;
			newY = (y - m_initialPointClick.y) + 20;
			newX = (newX + newY) / 2;
			dynamic_cast<vgSquare*>(m_newObject)->setDimension(newX);
			break;
		case PrimitiveType::Rectangle:
			newX = (x - m_initialPointClick.x) + 20;
			newY = (y - m_initialPointClick.y) + 20;
			dynamic_cast<vgRectangle*>(m_newObject)->setDimension(ofPoint(newX, newY));
			break;
		case PrimitiveType::Triangle:
			newX = (x - m_initialPointClick.x) + 20;
			newY = (y - m_initialPointClick.y) + 20;
			dynamic_cast<vgTriangle*>(m_newObject)->setDimension(ofPoint(newX, newY));
			break;
		case PrimitiveType::StripedCircles:
			newX = 2 * (x - m_initialPointClick.x);
			newY = 2 * (y - m_initialPointClick.y);
			newX = sqrt(newX * newX + newY * newY);
			dynamic_cast<StripedCircle*>(m_newObject)->setRadius(newX);
			break;
		case PrimitiveType::GeometricPattern:
			newX = (x - m_initialPointClick.x) + 20;
			newY = (y - m_initialPointClick.y) + 20;
			newX = (newX + newY) / 2;
			dynamic_cast<GeometricPattern*>(m_newObject)->setDimension(newX);
			break;
		default:
			break;
	}
}

Object* VectorGraphicsInitializer::mousePressed(int x, int y, int button) {
	if (!m_vectorGraphicsDrawingMode)
		return nullptr;

	m_drawing = true;
	m_initialPointClick = ofPoint(x, y);

	ofColor color1 = ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
	ofColor color2 = ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
	int nbStrips = (int)ofRandom(20, 40);

	switch (m_primitiveTypeToDraw) {
		case PrimitiveType::Ellipse:
			m_newObject = new vgEllipse(x, y, ofPoint(20, 20), m_fillColor, m_lineWidth, m_lineColor);
			return m_newObject;
		case PrimitiveType::Circle:
			m_newObject = new vgCircle(x, y, 20, m_fillColor, m_lineWidth, m_lineColor);
			return m_newObject;
		case PrimitiveType::Square:
			m_newObject = new vgSquare(x - 20, y - 20, 20, m_fillColor, m_lineWidth, m_lineColor);
			return m_newObject;
		case PrimitiveType::Rectangle:
			m_newObject = new vgRectangle(x - 20, y - 20, ofPoint(20, 20), m_fillColor, m_lineWidth, m_lineColor);
			return m_newObject;
		case PrimitiveType::Triangle:
			m_newObject = new vgTriangle(x - 20, y - 20, ofPoint(20, 20), m_fillColor, m_lineWidth, m_lineColor);
			return m_newObject;
		case PrimitiveType::StripedCircles:
			m_newObject = new StripedCircle(x, y, 20, color1, color2, nbStrips);
			return m_newObject;
		case PrimitiveType::GeometricPattern:
			m_newObject = new GeometricPattern(x - 20, y - 20, 20);
			return m_newObject;
		default:
			return nullptr;
	}
}

void VectorGraphicsInitializer::mouseReleased(int x, int y, int button) {
	m_newObject = nullptr;
	m_drawing = false;
}

void VectorGraphicsInitializer::keyPressed(int key) {
	if (key == KEY::P) {
		if (m_drawing)
			return;
		setNextPrimitiveType();
	}
}

void VectorGraphicsInitializer::disableDrawingMode() {
	m_vectorGraphicsDrawingMode = false;
	m_primitiveTypeToDraw = PrimitiveType::GeometricPattern;
}

void VectorGraphicsInitializer::drawStatus(const Window& window) {
	if (m_vectorGraphicsDrawingMode)
		m_font.drawString("Vector drawing mode activated : Drawing " + getDrawingType(), window.getX() + 10, window.getY() + 23);
}

void VectorGraphicsInitializer::setNextPrimitiveType() {
	if (m_primitiveTypeToDraw == PrimitiveType::GeometricPattern && m_vectorGraphicsDrawingMode == true) {
		m_vectorGraphicsDrawingMode = false;
		return;
	}
	m_vectorGraphicsDrawingMode = true;

	switch (m_primitiveTypeToDraw) {
		case PrimitiveType::Circle:
			m_primitiveTypeToDraw = PrimitiveType::Ellipse;
			break;
		case PrimitiveType::Ellipse:
			m_primitiveTypeToDraw = PrimitiveType::Rectangle;
			break;
		case PrimitiveType::Rectangle:
			m_primitiveTypeToDraw = PrimitiveType::Square;
			break;
		case PrimitiveType::Square:
			m_primitiveTypeToDraw = PrimitiveType::Triangle;
			break;
		case PrimitiveType::Triangle:
			m_primitiveTypeToDraw = PrimitiveType::StripedCircles;
			break;
		case PrimitiveType::StripedCircles:
			m_primitiveTypeToDraw = PrimitiveType::GeometricPattern;
			break;
		case PrimitiveType::GeometricPattern:
			m_primitiveTypeToDraw = PrimitiveType::Circle;
			break;
		default:
			break;
	}
}

std::string VectorGraphicsInitializer::getDrawingType() {
	switch (m_primitiveTypeToDraw) {
		case PrimitiveType::Circle:
			return "Circles";
		case PrimitiveType::Ellipse:
			return "Ellipses";
		case PrimitiveType::Rectangle:
			return "Rectangles";
		case PrimitiveType::Square:
			return "Squares";
		case PrimitiveType::Triangle:
			return "Triangles";
		case PrimitiveType::StripedCircles:
			return "Striped Circles";
		case PrimitiveType::GeometricPattern:
			return "Geometric Pattern";
		default:
			return "";
		}
}

void VectorGraphicsInitializer::setLineWidth(int lineWidth) {
	m_lineWidth = lineWidth;
}