#pragma once
#include "ofxDatGui.h"
#include <iostream>
#include "../Domain/Object.h"
#include "../Tools/InputController.h"
#include "Themes.h"
#include "UndoRedo.h"

class TransformMenu {
public:
	TransformMenu();
	void setup(int width, int height, int paddingX, int paddingY);
	void setCamera(Camera* camera) { m_camera = camera; }
	~TransformMenu();
	void setHeight(int height);
	void mouseMoved(int x, int y);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseDragged(int x, int y, int button);
	void keyReleased(int key);

	void setActiveObject(const std::vector<Object*>& activeObjects);

	ofVec2f getBottomCoord() const;

	void update();
	void draw();

	void setEnabled(bool enabled);

private:
	int m_width;
	int m_height;
	int m_paddingX;
	int m_paddingY;

	Camera* m_camera;
	std::vector<Object*> m_activeObjects;

	ofxDatGuiLabel* m_positionLabel;
	ofxDatGuiTextInput* m_positionXInput;
	ofxDatGuiTextInput* m_positionYInput;
	ofxDatGuiTextInput* m_positionZInput;
	bool m_positionXInputClicked = false;
	bool m_positionYInputClicked = false;
	bool m_positionZInputClicked = false;

	ofxDatGuiLabel* m_rotationLabel;
	ofxDatGuiTextInput* m_rotationXInput;
	ofxDatGuiTextInput* m_rotationYInput;
	ofxDatGuiTextInput* m_rotationZInput;
	bool m_rotationXInputClicked = false;
	bool m_rotationYInputClicked = false;
	bool m_rotationZInputClicked = false;

	int m_labelWidth = 75;
	ofxDatGuiLabel* m_scaleLabel;
	ofxDatGuiTextInput* m_scaleXInput;
	ofxDatGuiTextInput* m_scaleYInput;
	ofxDatGuiTextInput* m_scaleZInput;
	bool m_scaleXInputClicked = false;
	bool m_scaleYInputClicked = false;
	bool m_scaleZInputClicked = false;

	ofPoint m_lastMousePosition;

	void setAllInputsUnfocusedExceptOne(ofxDatGuiTextInput* exception);

	void setupPositionInputs();
	void setupRotationInputs();
	void setupScaleInputs();

	void onPositionXChanged(ofxDatGuiTextInputEvent e);
	void onPositionYChanged(ofxDatGuiTextInputEvent e);
	void onPositionZChanged(ofxDatGuiTextInputEvent e);
	void onRotationXChanged(ofxDatGuiTextInputEvent e);
	void onRotationYChanged(ofxDatGuiTextInputEvent e);
	void onRotationZChanged(ofxDatGuiTextInputEvent e);
	void onScaleXChanged(ofxDatGuiTextInputEvent e);
	void onScaleYChanged(ofxDatGuiTextInputEvent e);
	void onScaleZChanged(ofxDatGuiTextInputEvent e);

	void moveActiveObjects();
	bool moveObjects = false;

	void scaleActiveObjects();
	bool scaleObjects = false;
	ofPoint m_lastMousePositionForScaling;

	void rotateXActiveObjects();
	bool rotateXObjects = false;
	void rotateYActiveObjects();
	bool rotateYObjects = false;
	void rotateZActiveObjects();
	bool rotateZObjects = false;

	std::string formatFloatToText(float number);
	bool validFloat(const std::string& text);
	float formatTextToFloat(const std::string& text);

	void setEverythingFocused(bool focused);

	UndoRedo m_undoRedo;
};