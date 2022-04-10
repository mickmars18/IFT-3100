#pragma once
#include <ofxDatGui.h>
#include "Themes.h"
#include "../Domain/Object.h"
#include "../Models/Model.h"

class LightingModeMenu {
public:
	LightingModeMenu();
	~LightingModeMenu();
	void setup(int posX, int posY, int width, int padding);

	void setObject(const std::vector<Object*>& objects);

	void draw();
	void update();
private:
	void onDropdownEvent(ofxDatGuiDropdownEvent e);

	ofTrueTypeFont m_font;
	ofxDatGuiDropdown* m_dropdown;

	std::vector<Object*> m_objects;

	std::string m_gouraudVertexShaderName = "shaders/gouraud_420_vs.glsl";
	std::string m_gouraudFragmentShaderName = "shaders/gouraud_420_fs.glsl";

	std::string m_phongVertexShaderName = "shaders/phong_420_vs.glsl";
	std::string m_phongFragmentShaderName = "shaders/phong_420_fs.glsl";

	std::string m_blinnPhongVertexShaderName = "shaders/blinn_phong_420_vs.glsl";
	std::string m_blinnPhongFragmentShaderName = "shaders/blinn_phong_420_fs.glsl";
};
