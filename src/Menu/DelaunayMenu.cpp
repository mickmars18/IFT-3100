#include "DelaunayMenu.h"

DelaunayMenu::DelaunayMenu() {
	m_label = new ofxDatGuiLabel("Delaunay options");
	m_generateButton = new ofxDatGuiButton("Generate");
	m_nbPointsSlider = new ofxDatGuiSlider("Number of points", 3.0f, 500.0f, m_defaultValue);
	m_colorButton = new ofxDatGuiButton("Black and white");

	m_label->setTheme(Themes::getLabelTheme());
	m_generateButton->setTheme(Themes::getLabelTheme());
	m_nbPointsSlider->setTheme(Themes::getThemeSlider());
	m_colorButton->setTheme(Themes::getLabelTheme());

	m_nbPointsSlider->onSliderEvent(this, &DelaunayMenu::onNbPointsSliderEvent);
	m_generateButton->onButtonEvent(this, &DelaunayMenu::onGenerateButtonEvent);
	m_colorButton->onButtonEvent(this, &DelaunayMenu::onColorButtonEvent);

	m_nbPoints = m_defaultValue;
}

void DelaunayMenu::setup(int width, int posX, int posY, int paddingX, int paddingY) {
	m_label->setPosition(posX, posY);

	m_nbPointsSlider->setWidth(width, 0.5f);
	m_nbPointsSlider->setPosition(posX, m_label->getY() + m_label->getHeight() + paddingY);

	m_colorButton->setWidth(width);
	m_colorButton->setPosition(posX, m_nbPointsSlider->getY() + m_nbPointsSlider->getHeight() + paddingY);

	m_generateButton->setWidth(width);
	m_generateButton->setPosition(posX, m_colorButton->getY() + m_colorButton->getHeight() + paddingY);
}



void DelaunayMenu::update() {
	m_label->update();
	m_generateButton->update();
	m_nbPointsSlider->update();
	m_colorButton->update();
}

void DelaunayMenu::draw() {
	m_label->draw();
	m_generateButton->draw();
	m_nbPointsSlider->draw();
	m_colorButton->draw();
}

void DelaunayMenu::setObjects(std::vector<Object*> objects) {
	m_objects.clear();
	for (size_t i = 0; i < objects.size(); i++) {
		if (objects[i]->getClassName() == "Delaunay") {
			m_objects.push_back(objects[i]);
		}
	}
}

void DelaunayMenu::generate() {
	for (size_t i = 0; i < m_objects.size(); i++) {
		Delaunay* delaunay = dynamic_cast<Delaunay*>(m_objects[i]);
		std::vector<glm::vec2> points;

		int pointsPerEdge = 10;
		int width = 900;
		int distanceToEdge = 25;
		int distancetoEdgePoints = 25;

		int posX1 = distanceToEdge;
		int posY1 = distanceToEdge;
		int posX2 = distanceToEdge + width - width / pointsPerEdge;
		for (size_t i = 0; i < pointsPerEdge; i++) {
			points.push_back(glm::vec2(posX1, posY1));
			points.push_back(glm::vec2(posX2, posY1));
			posY1 += width / pointsPerEdge;
		}
		posY1 = distanceToEdge;
		int posY2 = distanceToEdge + width - width / pointsPerEdge;
		posX1 = distanceToEdge + width / pointsPerEdge;
		for (size_t i = 1; i < pointsPerEdge - 1; i++) {
			points.push_back(glm::vec2(posX1, posY1));
			points.push_back(glm::vec2(posX1, posY2));
			posX1 += width / pointsPerEdge;
		}

		for (size_t i = 0; i < m_nbPoints; i++) {
			float x = ofRandom(distanceToEdge + distancetoEdgePoints, width - width / pointsPerEdge - distancetoEdgePoints);
			float y = ofRandom(distanceToEdge + distancetoEdgePoints, width - width / pointsPerEdge - distancetoEdgePoints);
			points.push_back(glm::vec2(x, y));
		}

		delaunay->setPoints(points);
	}
}

void DelaunayMenu::onGenerateButtonEvent(ofxDatGuiButtonEvent e) {
	generate();
}

void DelaunayMenu::onColorButtonEvent(ofxDatGuiButtonEvent e) {
	for (size_t i = 0; i < m_objects.size(); i++) {
		Delaunay* delaunay = dynamic_cast<Delaunay*>(m_objects[i]);
		bool newColorMode = !delaunay->getColorMode();
		delaunay->setColorMode(newColorMode);
		if (newColorMode) {
			m_colorButton->setLabel("Color");
		}
		else {
			m_colorButton->setLabel("Black and white");
		}
		generate();
	}
}

void DelaunayMenu::onNbPointsSliderEvent(ofxDatGuiSliderEvent e) {
	m_nbPointsSlider->setValue((int)e.value);
	m_nbPoints = (int)e.value;
	generate();
}

DelaunayMenu::~DelaunayMenu() {
	delete m_label;
	delete m_nbPointsSlider;
	delete m_generateButton;
	delete m_colorButton;
}