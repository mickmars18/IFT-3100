#pragma once
#include "ofxDatGui.h"
#include "../Domain/Object.h"
#include "ColorPicker.h"
#include "SceneMenu.h"
#include "IObserver.h"
#include "TransformMenu.h"
#include "ImageSamplingSlider.h"
#include "RandomizeButton.h"
#include "../Image/ImageSampling.h"
#include "VectorGraphicsMenu.h"
#include "Cursor.h"
#include "IcosphereMenu.h"
#include "AxisGizmo.h"
#include "ToneMappingMenu.h"
#include "LightingModeMenu.h"
#include "LightMenu.h"
#include "ShininessSlider.h"
#include "RT_Menu.h"
#include "DelaunayMenu.h"
#include "NoiseTextureMenu.h"
#include "../Image/NoiseTexture.h"
#include "PBR_Menu.h"

class Menu : public IObserver {
public:
	Menu();
	~Menu();
	void setup(int width, int paddingX, int paddingY);
	void setObjects(std::list<Object*> objects);
	void setCamera(Camera* camera) { m_transformMenu.setCamera(camera); }
	void update();
	void draw();
	void drawRectangle();

	void setActiveObject(Object* object);
	std::vector<Object*> getActiveObject() const { return m_activeObject; }

	void updateActiveObject(Object* object);
	void resetSceneMenu(std::list<Object*>& objects);

	void mouseMoved(int x, int y);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseDragged(int x, int y, int button);
	void keyReleased(int key);

	void setImageSamplingObject(ImageSampling* imageSampling);

	ColorPicker* getColorPicker() { return &m_colorPicker; }
	void setVectorGraphicsMode(bool vectorGraphicsMode) { m_vectorGraphicsMode = vectorGraphicsMode; }
	void setBackgroundToVectorGraphicsMenu(Background* background);
	void setVectorGraphicsInitializer(VectorGraphicsInitializer* vectorGraphicsInitializer);

	void setToneMappingMenuActiveObjects(const std::vector<Object*>& object) { m_toneMappingMenu.setActiveObjects(object); }

	void showToneMapping(bool visible) { m_showToneMappingMenu = visible; }

	void setLightController(LightsController* lightController);

	void setRTApp(RT_App* rt_app) { m_RT_Menu.setRT_App(rt_app); };
	void setRTMode(bool enable) { m_RT_Mode = enable; }

	void setNoiseTexture(NoiseTexture* noiseTexture) { m_noiseTextureMenu.setTexture(noiseTexture); }
	void showNoiseTextureMenu(bool show) { m_showNoiseTextureMenu = show; }

private:
	std::vector<Object*> m_activeObject;
	bool atLeastOneObjectHasColorAttribute() const;
	bool activeObjectsAreAllClass(const std::string& className);
	bool atLeastOneActiveObjectIsOfClass(const std::string& className);
	bool objectInActiveObjects(Object* object);

	int m_width;
	int m_paddingX;
	int m_paddingY;

	ofxDatGuiTextInput* m_name;
	ofxDatGuiTheme* m_inputTheme;

	TransformMenu m_transformMenu;
	ToneMappingMenu m_toneMappingMenu;

	ImageSamplingSlider* m_imageSamplingSlider;
	RandomizeButton m_randomizeButton;
	ShininessSlider* m_shininessSlider;

	ColorPicker m_colorPicker;

	ofTrueTypeFont m_font;

	SceneMenu m_sceneMenu;

	VectorGraphicsMenu* m_vectorGraphicsMenu;
	bool m_vectorGraphicsMode = false;

	IcosphereMenu* m_icosphereMenu;

	LightingModeMenu m_lightingModeMenu;
	LightMenu m_lightMenu;

	Cursor* m_cursor;
	AxisGizmo m_axisGizmo;

	RT_Menu m_RT_Menu;
	DelaunayMenu m_delaunayMenu;

	bool m_showNoiseTextureMenu = false;
	NoiseTextureMenu m_noiseTextureMenu;

	PBR_Menu m_PBR_Menu;

	void nameChanged(ofxDatGuiTextInputEvent e);
	void notifyActiveObjectChanged();

	bool m_showToneMappingMenu = false;

	bool m_RT_Mode = false;
};