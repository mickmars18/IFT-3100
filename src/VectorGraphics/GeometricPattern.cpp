#include "GeometricPattern.h"

GeometricPattern::GeometricPattern(int x, int y, int dimension) :
	m_dimension(dimension)
{
	setName("Geometric Pattern");
	m_transform.setPosition(x, y, 0);

	initForms();
}

void GeometricPattern::initForms() {
	m_colors.clear();
	m_forms.clear();

	for (size_t i = 0; i < m_nbColors; i++) {
		m_colors.push_back(ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)));
	}

	std::vector<std::vector<Forms>> forms;
	for (size_t i = 0; i < m_nbColumn; i++) {
		forms.clear();
		for (size_t j = 0; j < m_nbColumn; j++) {
			std::vector<Forms> form = getRandomForms();
			forms.push_back(form);
		}
		m_forms.push_back(forms);
	}
}

std::vector<ofColor> GeometricPattern::getRandomColors(int nbColors) {
	std::vector<ofColor> result;
	result.reserve(nbColors);
	for (int i = 0; i < nbColors; i++) {
		result.push_back(getRandomColor());
	}
	return result;
}

ofColor GeometricPattern::getRandomColor() {
	int randomIndex = (int)ofRandom(0, m_nbColors - 1);
	return m_colors[randomIndex];
}

std::vector<GeometricPattern::Forms> GeometricPattern::getRandomForms() {
	int nbSubdivision = (int)ofRandom(1.0f, 5.0f);
	int nbForms = nbSubdivision;
	std::vector<Forms> form;
	for (size_t i = 0; i < nbForms * nbForms; i++) {
		form.push_back(getRandomForm());
	}
	return form;
}

GeometricPattern::Forms GeometricPattern::getRandomForm() {
	Forms result;
	int randomIndex = (int)ofRandom(0.0f, (float)m_allForms.size());
	result.m_form = m_allForms[randomIndex];

	if (result.m_form == Form::TwoTriangle0 || result.m_form == Form::TwoTriangle1) {
		result.m_colors.push_back(getRandomColor());
		result.m_colors.push_back(getRandomColor());
	}
	if (result.m_form == Form::FourTriangle) {
		result.m_colors.push_back(getRandomColor());
		result.m_colors.push_back(getRandomColor());
		result.m_colors.push_back(getRandomColor());
		result.m_colors.push_back(getRandomColor());
	}
	else {
		result.m_colors.push_back(getRandomColor());
	}
	return result;
}

std::string GeometricPattern::getClassName() {
	return "GeometricPattern";
}

void GeometricPattern::update() {

}

void GeometricPattern::draw(const Window& window, const Camera& camera) {
	ofSetColor(ofColor::white);
	ofDrawRectangle(m_transform.getPosition().x, m_transform.getPosition().y,
		m_dimension, m_dimension);
	
	ofSetColor(ofColor::black);
	float sizeX = (float)m_dimension / (float)m_nbColumn;
	float sizeY = (float)m_dimension / (float)m_nbColumn;
	for (size_t i = 0; i < m_nbColumn; i++) {
		for (size_t j = 0; j < m_nbColumn; j++) {
			int posX = m_transform.getPosition().x + i * sizeX;
			int posY = m_transform.getPosition().y + j * sizeY;
			drawForms(m_forms[i][j], posX, posY, sizeX, sizeY);
		}
	}

	ofSetColor(255);
}

void GeometricPattern::drawForms(const std::vector<Forms>& forms, int posX, int posY, float sizeX, float sizeY) {
	int nbForms = forms.size();
	int formsPerLine = (int)sqrt(nbForms);
	sizeX = sizeX / (float)formsPerLine;
	sizeY = sizeY / (float)formsPerLine;
	for (size_t i = 0; i < formsPerLine; i++) {
		for (size_t j = 0; j < formsPerLine; j++) {
			drawForm(forms[i * formsPerLine + j],
				posX + i * sizeX, 
				posY + j * sizeY, 
				sizeX, sizeY);
		}
	}
}

void GeometricPattern::drawForm(Forms form, int posX, int posY, float sizeX, float sizeY) {
	ofSetColor(form.m_colors[0]);
	switch (form.m_form) {
	case Form::Circle:
		ofDrawEllipse(posX + sizeX / 2, posY + sizeY / 2, sizeX, sizeY);
		break;
	case Form::Rectangle:
		ofDrawRectangle(posX, posY, sizeX, sizeY);
		break;
	case Form::Triangle0:
		drawTriangle0(posX, posY, sizeX, sizeY);
		break;
	case Form::Triangle1:
		drawTriangle1(posX, posY, sizeX, sizeY);
		break;
	case Form::Triangle2:
		drawTriangle2(posX, posY, sizeX, sizeY);
		break;
	case Form::Triangle3:
		drawTriangle3(posX, posY, sizeX, sizeY);
		break;
	case Form::TwoTriangle0:
		drawTriangle0(posX, posY, sizeX, sizeY);
		ofSetColor(form.m_colors[1]);
		drawTriangle1(posX, posY, sizeX, sizeY);
		break;
	case Form::TwoTriangle1:
		drawTriangle2(posX, posY, sizeX, sizeY);
		ofSetColor(form.m_colors[1]);
		drawTriangle3(posX, posY, sizeX, sizeY);
		break;
	case Form::FourTriangle:
		drawFourTriangle(form.m_colors, posX, posY, sizeX, sizeY);
		break;
	}
}

void GeometricPattern::drawTriangle0(int posX, int posY, float sizeX, float sizeY) {
	ofVec2f point1 = ofVec2f(posX, posY);
	ofVec2f point2 = ofVec2f(posX, posY + sizeX);
	ofVec2f point3 = ofVec2f(posX + sizeX, posY + sizeX);
	ofDrawTriangle(point1, point2, point3);
}

void GeometricPattern::drawTriangle1(int posX, int posY, float sizeX, float sizeY) {
	ofVec2f point1 = ofVec2f(posX, posY);
	ofVec2f point2 = ofVec2f(posX + sizeX, posY);
	ofVec2f point3 = ofVec2f(posX + sizeX, posY + sizeX);
	ofDrawTriangle(point1, point2, point3);
}

void GeometricPattern::drawTriangle2(int posX, int posY, float sizeX, float sizeY) {
	ofVec2f point1 = ofVec2f(posX + sizeX, posY);
	ofVec2f point2 = ofVec2f(posX + sizeX, posY + sizeX);
	ofVec2f point3 = ofVec2f(posX, posY + sizeX);
	ofDrawTriangle(point1, point2, point3);
}

void GeometricPattern::drawTriangle3(int posX, int posY, float sizeX, float sizeY) {
	ofVec2f point1 = ofVec2f(posX, posY);
	ofVec2f point2 = ofVec2f(posX + sizeX, posY);
	ofVec2f point3 = ofVec2f(posX, posY + sizeX);
	ofDrawTriangle(point1, point2, point3);
}

void GeometricPattern::drawFourTriangle(const std::vector<ofColor>& colors, int posX, int posY, float sizeX, float sizeY) {
	ofVec2f point1 = ofVec2f(posX, posY);
	ofVec2f point2 = ofVec2f(posX + sizeX, posY);
	ofVec2f point3 = ofVec2f(posX, posY + sizeX);
	ofVec2f point4 = ofVec2f(posX + sizeX, posY + sizeX);
	ofVec2f center = ofVec2f(posX + sizeX / 2.0f, posY + sizeX / 2.0f);

	ofSetColor(colors[0]);
	ofDrawTriangle(point1, center, point3);

	ofSetColor(colors[1]);
	ofDrawTriangle(point1, center, point2);

	ofSetColor(colors[2]);
	ofDrawTriangle(point2, center, point4);

	ofSetColor(colors[3]);
	ofDrawTriangle(point4, center, point3);
}