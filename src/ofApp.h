#pragma once

#include <iostream>
#include "ofMain.h"
#include "Domain/Window.h"
#include "Menu/Menu.h"
#include "Tools/InputController.h"
#include "Domain/SceneGraph.h"
#include "Domain/Object.h"
#include "Image/Image.h"
#include "Tools/AnimationSaver.h"
#include "Menu/SaveScreen.h"
#include "Image/ImageSampling.h"
#include "Domain/Camera.h"
#include "Domain/Background.h"
#include "VectorGraphics/VectorGraphicsInitializer.h"
#include "Models/Model.h"
#include "Models/Cube.h"
#include "Models/Icosphere.h"
#include "Domain/Grid.h"
#include "Domain/CameraController.h"
#include "Helper/Log.h"
#include "VectorGraphics/Line.h"
#include "Domain/Texture.h"
#include "Models/Skybox.h"
#include "Models/Plane.h"
#include "Domain/Light.h"
#include "Helper/ModelTexturesHelper.h"
#include "Raytracing/RT_App.h"
#include "Topology/Delaunay.h"
#include "Image/NoiseTexture.h"
#include "PBR/PBR_Model.h"
#include "Topology/BezierCurve.h"
#include "Topology/BezierSurface.h"

class ofApp : public ofBaseApp{

public:
	void exit();

	void setup();
	void update();
	void draw();
	void drawScene();
	void drawSceneInWireframe();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseScrolled(int x, int y, float scrollX, float scrollY);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	Menu m_menu;

private:
	SceneGraph m_sceneGraph;
	bool m_isWireFrameMode = false;
	bool m_isOneScreen = true;
	void drawFullScreen();
	void drawHalfScreens();

	ofRectangle m_viewportFull;
	ofRectangle m_viewportHalfTop;
	ofRectangle m_viewportHalfBottom;
	void setupViewports();

	int m_menuWidth = 300;
	int m_paddingX = 5;
	int m_paddingY = 5;
	Window m_window;
	Camera* m_camera;
	AnimationSaver* m_animationSaver;
	SaveScreen* m_saveScreen;
	VectorGraphicsInitializer m_vectorGraphicsInitializer;
	Background m_background;
	Grid m_grid;
	Skybox m_skybox;
	CameraController m_cameraController;

	void addObjectToScene(Object* object);
	std::string getFileExtension(const std::string& filename);

	Texture* loadTexture(const std::string& filename, bool HDR = false);

	float m_currentTime;
	float m_lastTime;
	float m_deltaTime;
	ofVec2f m_lastMousePosition;

	void loadScene(int scene);
	void clearScene();
	void loadScene0();
	void loadScene1();
	void loadScene2();
	void loadScene3();
	void loadScene4();
	void loadScene5();
	void loadScene6();
	void loadScene7();
	void loadScene8();
	void loadScene9();
	void loadScene10();
	void loadScene11();

	std::vector<Texture*> m_textures;
	bool m_showGrid = true;
	bool m_showSkyBox = false;

	void setMaterials(Model* model1, Model* model2, Model* model3);
	Material m_material1;
	Material m_material2;
	Material m_material3;

	ModelTexturesHelper m_modelTexturesHelper;

	Light* createLight(LightMode lightMode);
	LightsController* m_lightsController;

	Model* createModel(const std::string& filename, bool HDR=false);
	PBR_Model* createPBRModel(const std::string& filename);

	BezierCurve* m_bezierCurve = nullptr;

	RT_App m_RT_App;
	bool m_RT_Mode = false;
	void drawRT();
	void enableRTMode();
	void disableRTMode();
	void setupRT();
};
