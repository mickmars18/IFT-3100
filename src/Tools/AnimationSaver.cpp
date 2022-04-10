#include "AnimationSaver.h"

void AnimationSaver::saveAnimation(int numberOfImages, int imagesPerSecond, const Window& window) {
	std::cout << "Saving Animation" << std::endl;
	m_window = &window;
	m_timer.startTimer((float)numberOfImages / (float)imagesPerSecond, imagesPerSecond);
	m_frameNumber = 1;
}

void AnimationSaver::update() {
	if (m_timer.isTimerRunning() && m_timer.newInterval()) {
		saveImage();
		m_frameNumber++;
	}
}

void AnimationSaver::saveImage() {
	ofImage screen;
	screen.allocate(m_window->getWidth(), m_window->getHeight(), OF_IMAGE_COLOR);
	screen.grabScreen(m_window->getX(), m_window->getY(), m_window->getWidth(), m_window->getHeight());
	string imageName = getFilename();
	screen.save(imageName);
	std::cout << "Image saved to : " << imageName << std::endl;
}

std::string AnimationSaver::getFilename() {
	std::string extension = "jpg";
	string time_stamp = ofGetTimestampString("-%y%m%d-%H%M%S-%i");
	std::string filename = "Image"  + time_stamp + "." + extension;
	return "Images saved/" + filename;
}