#include "Texture.h"
#include <vector>

Texture::Texture(const std::string& filename, bool HDR) {
	ofDisableArbTex();
	m_image = new ofImage(filename);
	m_texture = new ofTexture();

	if (HDR) {
		ofFloatPixels pixels = m_image->getPixels();
		m_texture->loadData(pixels);
	}
	else {
		bool success = ofLoadImage(*m_texture, filename);
		if (!success) {
			std::cout << "Unable to load texture at path : " + filename << std::endl;
			return;
		}
	}
	m_texture->generateMipmap();
	m_texture->setTextureMinMagFilter(GL_LINEAR_MIPMAP_LINEAR, GL_NEAREST);
	m_texture->setTextureWrap(GL_REPEAT, GL_REPEAT);

	m_name = filename;
}

Texture::Texture(const ofTexture* RT_Texture) {
	m_image = nullptr;
	m_texture = new ofTexture(*RT_Texture);
}

void Texture::bind(int textureLocation) {
	m_texture->bind(textureLocation);
}

void Texture::unbind(int textureLocation) {
	m_texture->unbind(textureLocation);
}

std::string Texture::getName() const {
	return m_name;
}

Texture* Texture::getTextureWithGaussianBlurFilter() const {
	std::vector<float> kernel = { 1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f,
								  2.0f / 16.0f, 4.0f / 16.0f, 2.0f / 16.0f,
								  1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f };

	ofPixels newPixels;
	modifyPixelsWithKernel(newPixels, m_image->getPixels(), kernel);

	ofTexture* modifiedTexture = new ofTexture();
	modifiedTexture->allocate(newPixels);
	Texture* result = new Texture(modifiedTexture);
	delete modifiedTexture;

	return result;
}

Texture* Texture::getTextureWithRidgeDetectionFilter() const {
	std::vector<float> kernel = { -1.0f, -1.0f, -1.0f,
								  -1.0f,  8.0f, -1.0f,
								  -1.0f, -1.0f, -1.0f };

	ofPixels newPixels;
	modifyPixelsWithKernel(newPixels, m_image->getPixels(), kernel);

	ofTexture* modifiedTexture = new ofTexture();
	modifiedTexture->allocate(newPixels);
	Texture* result = new Texture(modifiedTexture);
	delete modifiedTexture;

	return result;
}

Texture* Texture::getTextureWithSharpenFilter() const {
	std::vector<float> kernel = {  0.0f, -1.0f,  0.0f,
								  -1.0f,  5.0f, -1.0f,
								   0.0f, -1.0f,  0.0f };

	ofPixels newPixels;
	modifyPixelsWithKernel(newPixels, m_image->getPixels(), kernel);

	ofTexture* modifiedTexture = new ofTexture();
	modifiedTexture->allocate(newPixels);
	Texture* result = new Texture(modifiedTexture);
	delete modifiedTexture;

	return result;
}

void Texture::modifyPixelsWithKernel(ofPixels& newPixels, const ofPixels& originalPixels, const std::vector<float>& kernel) const {
	newPixels.allocate(originalPixels.getWidth(), originalPixels.getHeight(), ofImageType::OF_IMAGE_COLOR);
	
	int width = newPixels.getWidth();
	int height = newPixels.getHeight();
	for (size_t i = 0; i < width; i++) {
		for (size_t j = 0; j < height; j++) {
			size_t index = 3 * (i + j * width);
			newPixels[index] = originalPixels[index];
			newPixels[index + 1] = originalPixels[index + 1];
			newPixels[index + 2] = originalPixels[index + 2];
		}
	}

	for (size_t i = 1; i < width - 1; i++) {
		for (size_t j = 1; j < height - 1; j++) {
			size_t index1 = 3 * ((i - 1) + (j + 1) * width);
			size_t index2 = 3 * ((i)+(j + 1) * width);
			size_t index3 = 3 * ((i + 1) + (j + 1) * width);

			size_t index4 = 3 * ((i - 1) + (j)*width);
			size_t index5 = 3 * ((i)+(j)*width);
			size_t index6 = 3 * ((i + 1) + (j)*width);

			size_t index7 = 3 * ((i - 1) + (j - 1) * width);
			size_t index8 = 3 * ((i)+(j - 1) * width);
			size_t index9 = 3 * ((i + 1) + (j - 1) * width);

			for (size_t k = 0; k < 3; k++) {

				int color = kernel[0] * (float)originalPixels[index1 + k] + kernel[1] * (float)originalPixels[index4 + k] + kernel[2] * (float)originalPixels[index7 + k] +
					kernel[3] * (float)originalPixels[index2 + k] + kernel[4] * (float)originalPixels[index5 + k] + kernel[5] * (float)originalPixels[index8 + k] +
					kernel[6] * (float)originalPixels[index3 + k] + kernel[7] * (float)originalPixels[index6 + k] + kernel[8] * (float)originalPixels[index9 + k];
				newPixels[index5 + k] = ofClamp(color, 0, 255);
			}
		}
	}
}

Texture* Texture::getTextureWithLut(const Lut& lut) const {
	ofPixels originalPixels = m_image->getPixels();
	ofPixels newPixels;
	newPixels.allocate(originalPixels.getWidth(), originalPixels.getHeight(), ofImageType::OF_IMAGE_COLOR);
	int width = newPixels.getWidth();
	int height = newPixels.getHeight();

	int ii = 0;
	int jj = 0;

	for (size_t i = 0; i < width; i++) {
		for (size_t j = 0; j < height; j++) {
			size_t index = 3 * (i + j * width);

			int originalRed = originalPixels[index];
			int originalGreen = originalPixels[index + 1];
			int originalBlue = originalPixels[index + 2];

			ofColor lookedUpColor = lut.getColor(originalRed, originalGreen, originalBlue);

			newPixels[index] = lookedUpColor.r;
			newPixels[index + 1] = lookedUpColor.g;
			newPixels[index + 2] = lookedUpColor.b;
		}
	}


	ofTexture* modifiedTexture = new ofTexture();
	modifiedTexture->allocate(newPixels);
	Texture* result = new Texture(modifiedTexture);
	delete modifiedTexture;

	return result;
}

Texture::~Texture() {
	delete m_texture;
}