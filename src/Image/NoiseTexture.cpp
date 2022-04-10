#include "NoiseTexture.h"

NoiseTexture::NoiseTexture() {
	m_texture = new ofTexture();
	setTexture(1000, 1000, 100.0, 0.0);
}

void NoiseTexture::setTexture(int textureWidth, int textureHeight, double scale, double woodScale) {
	ofFloatPixels pixels;
	pixels.allocate(textureWidth, textureHeight, ofImageType::OF_IMAGE_COLOR);

	PerlinNoise perlinNoise;

	int i = 0;
	for (int x = 0; x < textureWidth; x++) {
		for (int y = 0; y < textureHeight; y++) {
			double u = (double)x / (double)textureWidth;
			double v = (double)y / (double)textureHeight;

			double noise = perlinNoise.noise(scale * u, scale * v, 0.8);
			if (woodScale > 0.0) {
				noise = woodScale * perlinNoise.noise(u, v, 0.8);
				noise = noise - floor(noise);
			}

			pixels[i++] = noise;
			pixels[i++] = noise;
			pixels[i++] = noise;
		}
	}

	m_texture->allocate(pixels);
}

NoiseTexture::~NoiseTexture() {
	delete m_texture;
}