#pragma once
#include "../Models/Model.h"

class ModelTexturesHelper {
public:
	ModelTexturesHelper();
	~ModelTexturesHelper();
	void setup(Model* model, const std::vector<Texture*>& textures);
	void enter();
	void left();
	void right();
	void up();
	void down();

	Texture* getSelection() const { return m_textures[m_textureSelection]; }
private:
	Model* m_model;
	std::vector<Texture*> m_textures;

	int m_textureSelection = 0;
	int m_meshSelection = 0;

	Texture* m_pink;
	Texture* m_gray;

	std::vector<string> m_results;
};
