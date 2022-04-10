#pragma once
#include "ofxDatGui.h"
#include "../Domain/Object.h"
#include "ISubject.h"
#include "../Tools/InputController.h"
#include "Themes.h"

class SceneMenu : public ISubject {
public:
	void setup(int width, int posX, int posY, int paddingX, int paddingY);
	void resetObjects(std::list<Object*>& objects);
	void organiseObjectList(std::list<Object*>& objects);
	void insertNextNode(Object* node, std::list<Object*>& objects);
	void setupPosition();
	void update();
	void onButtonClicked(ofxDatGuiButtonEvent e);
	void setObjectName(Object* object, const std::string& newName);
	void draw();
	void drawSelection(const std::vector<Object*>& object);

	void mousePressed(int x, int y, int button);

	~SceneMenu();

	void Attach(IObserver* observer) override {
		m_observers.push_back(observer);
	}
	void Detach(IObserver* observer) override {
		m_observers.remove(observer);
	}
	void Notify(Object* object) override {
		std::list<IObserver*>::iterator iterator = m_observers.begin();
		while (iterator != m_observers.end()) {
			(*iterator)->updateActiveObject(object);
			++iterator;
		}
	}

private:
	ofTrueTypeFont m_font;
	std::list<std::pair<ofxDatGuiButton*, Object*>> m_buttons;

	ofVec2f m_sceneTextPosition;

	int m_width;
	int m_posX;
	int m_posY;
	int m_paddingX;
	int m_paddingY;
	int m_textWidth;
	int m_textHeight;

	std::list<IObserver*> m_observers;

	void drawRectangle();
};
