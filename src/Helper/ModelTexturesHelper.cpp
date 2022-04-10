#include "ModelTexturesHelper.h"

ModelTexturesHelper::ModelTexturesHelper() {
	m_pink = new Texture("pink.png");
	m_gray = new Texture("gray.png");
}

void ModelTexturesHelper::setup(Model* model, const std::vector<Texture*>& textures) {
	m_model = model;

	m_textures.clear();
	for (size_t i = 0; i < textures.size(); i++) {
		m_textures.push_back(textures[i]);
	}

	m_model->getMaterial()->setAllDiffuseTextures(m_gray);
	m_meshSelection = 0;
	m_model->getMaterial()->setDiffuseTexture(m_meshSelection, getSelection());
}

void ModelTexturesHelper::enter() {
	m_results.push_back(std::to_string(m_meshSelection) + " : " + getSelection()->getName());
	up();
}

void ModelTexturesHelper::left() {
	m_textureSelection--;
	if (m_textureSelection < 0)
		m_textureSelection = m_textures.size() - 1;
	m_model->getMaterial()->setDiffuseTexture(m_meshSelection, getSelection());
}

void ModelTexturesHelper::right() {
	m_textureSelection++;
	if (m_textureSelection >= m_textures.size())
		m_textureSelection = 0;
	m_model->getMaterial()->setDiffuseTexture(m_meshSelection, getSelection());
}

void ModelTexturesHelper::up() {
	m_meshSelection++;
	if (m_meshSelection > m_model->getNumOfMesh() - 1)
		m_meshSelection = 0;
	
	m_textureSelection = m_textures.size() - 1;
	m_model->getMaterial()->setDiffuseTexture(m_meshSelection, m_pink);
}

void ModelTexturesHelper::down() {
	m_meshSelection--;
	if (m_meshSelection < 0)
		m_meshSelection = m_model->getNumOfMesh() - 1;

	m_textureSelection = 0;
	m_model->getMaterial()->setDiffuseTexture(m_meshSelection, m_pink);
}

ModelTexturesHelper::~ModelTexturesHelper() {
	delete m_pink;
	delete m_gray;

	for (size_t i = 0; i < m_results.size(); i++) {
		std::cout << m_results[i] << std::endl;
	}
}