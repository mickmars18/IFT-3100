#pragma once
#include "../Domain/Object.h"

class GeometricPattern : public Object {
public:
	GeometricPattern(int x, int y, int dimension);
	void initForms();
	std::string getClassName() override;
	void update() override;
	void draw(const Window& window, const Camera& camera) override;
	inline int getDimension() const { return m_dimension; }
	inline void setDimension(int dimension) { m_dimension = dimension; }
	virtual bool isVectorGraphics() const { return true; }
private:
	int m_dimension;
	int m_nbColors = 4;
	std::vector<ofColor> m_colors;
	ofColor getRandomColor();
	std::vector<ofColor> getRandomColors(int nbColors);

	int m_nbColumn = 12;

	enum class Form {
		Circle,
		Rectangle,
		Triangle0,
		Triangle1,
		Triangle2,
		Triangle3,
		TwoTriangle0,
		TwoTriangle1,
		FourTriangle,
		Empty
	};

	class Forms {
	public:
		Form m_form;
		std::vector<ofColor> m_colors;
	};

	std::vector<Form> m_allForms = {
		Form::Circle,
		Form::Circle,
		Form::Circle,
		Form::Circle,
		Form::Rectangle,
		Form::Rectangle,
		Form::Rectangle,
		Form::Rectangle,
		Form::Triangle0,
		Form::Triangle1,
		Form::Triangle2,
		Form::Triangle3,
		Form::TwoTriangle0,
		Form::TwoTriangle1,
		Form::TwoTriangle0,
		Form::TwoTriangle1,
		Form::FourTriangle,
		Form::FourTriangle,
		Form::FourTriangle,
		Form::FourTriangle,
		Form::Empty,
	};

	std::vector<std::vector<std::vector<Forms>>> m_forms;
	std::vector<std::vector<std::vector<ofColor>>> m_color;
	std::vector<Forms> getRandomForms();
	Forms getRandomForm();
	void drawForms(const std::vector<Forms>& forms, int posX, int posY, float sizeX, float sizeY);
	void drawForm(Forms form, int posX, int posY, float sizeX, float sizeY);
	void drawTriangle0(int posX, int posY, float sizeX, float sizeY);
	void drawTriangle1(int posX, int posY, float sizeX, float sizeY);
	void drawTriangle2(int posX, int posY, float sizeX, float sizeY);
	void drawTriangle3(int posX, int posY, float sizeX, float sizeY);
	void drawFourTriangle(const std::vector<ofColor>& colors, int posX, int posY, float sizeX, float sizeY);
};
