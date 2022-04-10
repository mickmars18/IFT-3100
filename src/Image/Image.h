#pragma once
#include "ofImage.h"
#include "ofMain.h"
#include "../Domain/Object.h"
#include "Histogram.h"
#include "../Camera.h"

class Image : public Object {
public:
	Image(const std::string& filename);
	~Image();
	std::string getClassName() { return "Image"; };
	void update() override;
	void draw(const Window& window, const Camera& camera) override;

	void setImage(const ofPixels& pixels);

	ofColor getColor() const override;
	void changeColor(const ofColor& color) override;
	void recalculateColorizedImage();
	void keyReleased(int key) override;
	std::string getFilenameFormatted(std::string filename) const;

	inline ofShader& getShader() { return m_shader; }

	bool hasColorAttribute() override { return true; }
private:
	ofImage* m_image;
	ofImage* m_imageColorized;
	ofColor m_color;
	Histogram* m_histogram;
	bool m_newColor;
	bool m_showHistogram;
};
