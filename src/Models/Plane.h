#pragma once
#include "../Domain/Object.h"
#include "../Domain/Texture.h"

class Plane : public Object {
public:
	Plane(int sizeX, int sizeY, Texture* RT_Texture = nullptr);
	void setTexture(Texture* RT_Texture);
	std::string getClassName() override;
	void update() override;
	void draw(const Window& window, const Camera& camera) override;
	void changeShaders(const std::string& vs, const std::string& fs);
private:
	int m_sizeX;
	int m_sizeY;

	ofMesh m_mesh;
	Texture* m_texture;
};
