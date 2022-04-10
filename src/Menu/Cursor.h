#pragma once
#include <graphics/ofImage.h>
#include <graphics/ofGraphics.h>
#include <app/ofAppRunner.h>
#include "../Tools/InputController.h"

class Cursor {
public:
	Cursor();
	~Cursor();
	void update();
	void draw();
private:
	ofImage* m_moveCursor;
	ofImage* m_scaleCursor;
	ofImage* m_rotateXCursor;
	ofImage* m_rotateYCursor;
	ofImage* m_rotateZCursor;

	void showCursor(bool& cursorToShow);

	bool m_showMoveCursor = false;
	bool m_showScaleCursor = false;
	bool m_showRotateXCursor = false;
	bool m_showRotateYCursor = false;
	bool m_showRotateZCursor = false;
};