#pragma once
#include <string>
#include <gl/ofTexture.h>
#include <graphics/ofImage.h>
#include "../Image/Lut.h"

class Texture {
public:
	Texture() {};
	Texture(const std::string& filename, bool hdr=false);
	Texture(const ofTexture* RT_Texture);
	void bind(int textureLocation);
	void unbind(int textureLocation);
	std::string getName() const;

	Texture* getTextureWithGaussianBlurFilter() const;
	Texture* getTextureWithRidgeDetectionFilter() const;
	Texture* getTextureWithSharpenFilter() const;

	Texture* getTextureWithLut(const Lut& lut) const;

	void modifyPixelsWithKernel(ofPixels& newPixels, const ofPixels& originalPixels, const std::vector<float>& kernel) const;

	~Texture();
protected:
	ofImage* m_image;

	ofTexture* m_texture;
	std::string m_name;
};
