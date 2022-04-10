#pragma once
#include "../Domain/Texture.h"
#include "../Helper/PerlinNoise.h"

class NoiseTexture : public Texture {
public:
	NoiseTexture();
    ~NoiseTexture();
    void setTexture(int textureWidth, int textureHeight, double scale, double woodScale);

private:
    double m_scale;
};