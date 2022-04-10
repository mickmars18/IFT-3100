#pragma once
#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofGLFWWindowSettings windowSettings;
	windowSettings.setSize(1600, 900);
	windowSettings.setGLVersion(3, 3);
	ofCreateWindow(windowSettings);

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
