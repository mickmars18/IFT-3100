#pragma once

#include "ofxDatGui.h"

class Themes {
public :
	static void init() {
		m_init = true;
		ofxDatGuiTextInput defaultInput("");
		m_themeNormal = defaultInput.getTheme();
		m_themeSmall = defaultInput.getTheme();
		m_themeLarge = defaultInput.getTheme();

		m_themeNormal.color.textInput.text = ofColor::white;
		m_themeSmall.color.textInput.text = ofColor::white;
		m_themeLarge.color.textInput.text = ofColor::white;

		m_themeNormal.stripe.label = ofColor::white;
		m_themeSmall.stripe.label = ofColor::white;
		m_themeLarge.stripe.label = ofColor::white;

		m_themeNormal.font.file = ofxDatGuiTheme::AssetPath + m_font;
		m_themeSmall.font.file = ofxDatGuiTheme::AssetPath + m_font;
		m_themeLarge.font.file = ofxDatGuiTheme::AssetPath + m_font;

		m_themeNormal.font.size = 8;
		m_themeSmall.font.size = 7;
		m_themeLarge.font.size = 9;

		m_themeNormal.init();
		m_themeSmall.init();
		m_themeLarge.init();

		m_themeLabel = m_themeNormal;
		m_themeLabel.stripe.label = ofColor(30,30,30);

		ofxDatGuiSlider slider("", 0, 1);
		m_themeSlider = slider.getTheme();
		m_themeSlider.font = m_themeNormal.font;
	}
	static ofxDatGuiTheme* getTextTheme() {
		if (!m_init) {
			init();
		}
		return &m_themeNormal;
	}

	static ofxDatGuiTheme* getTextThemeSmall() {
		if (!m_init) {
			init();
		}
		return &m_themeSmall;
	}

	static ofxDatGuiTheme* getTextThemeLarge() {
		if (!m_init) {
			init();
		}
		return &m_themeLarge;
	}
	static ofxDatGuiTheme* getLabelTheme() {
		if (!m_init) {
			init();
		}
		return &m_themeLabel;
	}
	static ofxDatGuiTheme* getThemeSlider() {
		if (!m_init) {
			init();
		}
		return &m_themeSlider;
	}
	static std::string getFontName() {
		return m_font;
	}
private:
	static std::string m_font;
	static ofxDatGuiTheme m_themeNormal;
	static ofxDatGuiTheme m_themeSmall;
	static ofxDatGuiTheme m_themeLarge;
	static ofxDatGuiTheme m_themeLabel;
	static ofxDatGuiTheme m_themeSlider;
	static bool m_init;
};
