#pragma once
#include "../Domain/Object.h"
#include "../Helper/HelperFunctions.h"
#include "../Helper/Log.h"

class VectorGraphicsImage : public Object {
public:
	VectorGraphicsImage(const std::string& filename);
	~VectorGraphicsImage();
	std::string getClassName() override;
	void update() override;
	void draw(const Window& window, const Camera& camera) override;

private:
	ofImage* m_image;
};