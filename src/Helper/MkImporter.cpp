#include "MkImporter.h"

std::vector<std::shared_ptr<Mesh>> MkImporter::loadModel(const std::string& filename) {

	std::string path = "C:/Users/AlexandreLaBoissonni/Bureau/Mika/bin/data/" + filename;
	m_scene = m_importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	if (!m_scene || m_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !m_scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << m_importer.GetErrorString() << std::endl;
		return std::vector<std::shared_ptr<Mesh>>();
	}

	m_directory = path.substr(0, path.find_last_of('/'));

    m_meshes.clear();
    m_materials.clear();
	processNode(m_scene->mRootNode, m_scene);

	return m_meshes;
}

void MkImporter::processNode(aiNode* node, const aiScene* scene) {
    // process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshes.push_back(processMesh(mesh, scene));
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

std::shared_ptr<Mesh> MkImporter::processMesh(aiMesh* mesh, const aiScene* scene) {
    std::shared_ptr<Mesh> resultingMesh = std::make_shared<Mesh>();
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        ofDefaultVertexType vertex;
        // process vertex positions, normals and texture coordinates
        vertex.x = mesh->mVertices[i].x;
        vertex.y = mesh->mVertices[i].y;
        vertex.z = mesh->mVertices[i].z;
        resultingMesh->addVertex(vertex);

        if (mesh->HasNormals()) {
            ofDefaultNormalType normal;
            normal.x = mesh->mNormals[i].x;
            normal.y = mesh->mNormals[i].y;
            normal.z = mesh->mNormals[i].z;
            resultingMesh->addNormal(normal);
        }

        if (mesh->mTextureCoords[0]) {
            ofDefaultTexCoordType textCoord;
            textCoord.x = mesh->mTextureCoords[0][i].x;
            textCoord.y = mesh->mTextureCoords[0][i].y;
            resultingMesh->addTexCoord(textCoord);
        }
        else {
            ofDefaultTexCoordType textCoord;
            textCoord.x = 0.0f;
            textCoord.y = 0.0f;
            resultingMesh->addTexCoord(textCoord);
        }

        if (mesh->mTangents) {
            glm::vec3 tangent;
            tangent.x = mesh->mTangents[i].x;
            tangent.y = mesh->mTangents[i].y;
            tangent.z = mesh->mTangents[i].z;
            resultingMesh->addColor(ofDefaultColorType(tangent.x, tangent.y, tangent.z, 1.0f));
        }
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            resultingMesh->addIndex(face.mIndices[j]);
    }

    if (mesh->mMaterialIndex <= 0) {
        ofMaterial material;
        m_materials.push_back(material);
        return resultingMesh;
    }

    ofMaterial material;
    aiMaterial* aiMaterial = scene->mMaterials[mesh->mMaterialIndex];
    aiUVTransform result;

    aiColor3D l_diffuse;
    aiMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, l_diffuse);

    aiColor3D l_ambient;
    aiMaterial->Get(AI_MATKEY_COLOR_AMBIENT, l_ambient);

    float l_specular_intensity = 5.0f;
    aiMaterial->Get(AI_MATKEY_SHININESS_STRENGTH, l_specular_intensity);

    aiColor3D l_specular;
    aiMaterial->Get(AI_MATKEY_COLOR_SPECULAR, l_specular);

    material.setDiffuseColor(ofFloatColor(l_diffuse.r, l_diffuse.g, l_diffuse.b));
    material.setSpecularColor(ofFloatColor(l_specular.r, l_specular.g, l_specular.b));
    material.setAmbientColor(ofFloatColor(l_ambient.r, l_ambient.g, l_ambient.b));
    material.setShininess(l_specular_intensity);

    m_materials.push_back(material);

    loadMaterialTextures(aiMaterial);

    return resultingMesh;
}

void MkImporter::loadMaterialTextures(aiMaterial* mat)
{
    aiString diffuseStr;
    mat->GetTexture(aiTextureType::aiTextureType_DIFFUSE, 0, &diffuseStr);
    std::string diffuseStrFormatted(diffuseStr.C_Str());
    diffuseStrFormatted = getFilenameWithoutPath(diffuseStrFormatted);
    m_diffuseTexturesPath.insert(std::make_pair(m_materials.size() - 1, diffuseStrFormatted));

    aiString normalStr;
    mat->GetTexture(aiTextureType::aiTextureType_HEIGHT, 0, &normalStr);
    std::string normalStrFormatted(diffuseStr.C_Str());
    normalStrFormatted = getFilenameWithoutPath(diffuseStrFormatted);
    m_normalsTexturesPath.insert(std::make_pair(m_materials.size() - 1, normalStrFormatted));
}