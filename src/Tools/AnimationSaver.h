#pragma once
#include "../Domain/Window.h"
#include "ofMain.h"
#include "../Helper/Timer.h"
#include <cstdio>


class AnimationSaver {
public:
	void saveAnimation(int numberOfImages, int imagesPerSecond, const Window& window);
	void update();
private:
	bool m_nowSaving;
	Timer m_timer;
	const Window* m_window;
	std::string getFilename();
	void saveImage();
	int m_frameNumber;
};