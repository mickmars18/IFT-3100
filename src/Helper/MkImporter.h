#pragma once
#include <ofxAssimpModelLoader/libs/assimp/include/assimp/Importer.hpp>
#include <ofxAssimpModelLoader/libs/assimp/include/assimp/scene.h>
#include <ofxAssimpModelLoader/libs/assimp/include/assimp/postprocess.h>
#include <vector>
#include <gl/ofMaterial.h>
#include "../Domain/Mesh.h"
#include "../Domain/Texture.h"
#include "../Helper/HelperFunctions.h"

class MkImporter {
public:
	MkImporter() {}
	std::vector<std::shared_ptr<Mesh>> loadModel(const std::string& filename);
	void processNode(aiNode* node, const aiScene* scene);
	std::shared_ptr<Mesh> processMesh(aiMesh* mesh, const aiScene* scene);

	ofMaterial getMaterialForMesh(int i) const {
		return m_materials[i];
	}

	std::map<int, std::string> getDiffuseTexturesPath() { return m_diffuseTexturesPath; }
	std::map<int, std::string> getNormalsTexturesPath() { return m_normalsTexturesPath; }

private:
	Assimp::Importer m_importer;
	const aiScene* m_scene;
	std::string m_directory;

	std::vector<std::shared_ptr<Mesh>> m_meshes;
	std::vector<ofMaterial> m_materials;
	std::map<int, std::string> m_diffuseTexturesPath;
	std::map<int, std::string> m_normalsTexturesPath;


	void loadMaterialTextures(aiMaterial* mat);
};
