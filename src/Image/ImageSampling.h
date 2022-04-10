#pragma once
#include "Image.h"
#include "../Domain/Object.h"

class ImageSampling : public Object {
public:
	ImageSampling(const std::string& image1, const std::string& image2);
	~ImageSampling();
	std::string getClassName() { return "ImageSampling"; }

	void update() override;
	void draw(const Window& window, const Camera& camera) override;

	void recalculateImage(float factor);
private:
	ofImage* m_image1;
	ofImage* m_image2;
	Image* m_imageToDraw;

	float m_factor = 0.5f;

	int m_width = 0;;
	int m_height = 0;

	void resizeImages();
};
