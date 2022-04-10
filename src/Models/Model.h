#pragma once
#include <iostream>
#include "../Domain/Object.h"
#include "../Helper/HelperFunctions.h"
#include "ofxAssimpModelLoader.h"
#include <limits>
#include "../Helper/Timer.h"
#include "Box.h"
#include "../Domain/Texture.h"
#include "../Domain/Material.h"
#include "../Domain/Light.h"
#include "../Domain/LightsController.h"
#include "../Helper/MkImporter.h"

class Model : public Object {
public:
	Model();
	Model(const std::string& filename);
	~Model();
	std::string getClassName() override;
	void update() override;
	void draw(const Window& window, const Camera& camera) override;
	void setDrawBox(bool drawBox) { m_drawBox = drawBox; }
	bool getDrawBox() const { return m_drawBox; }
	size_t getNumOfMesh() const { return m_mesh.size(); }

	Material* getMaterial() { return &m_material; }
	void setMaterial(const Material& material) { m_material = material; }

	float getShininess() const { return m_shininess; }
	void setShininess(float shininess) { m_shininess = shininess; }

	void setGeometryShaders(const std::string& vs, const std::string& fs, const std::string& gs);

	void setLightsController(LightsController* lightController);
	void setColorsFromLoadedMaterial();
	void resetAllColors();
	void flipNormalsOnTheYAxis();
	void setTileX(float tileX) { m_tileX = tileX; }
	void setTileY(float tileY) { m_tileY = tileY; }
	void setTile(float tile) { 
		m_tileX = tile;
		m_tileY = tile;
	}
	void setTile(float tileX, float tileY) {
		m_tileX = tileX;
		m_tileY = tileY;
	}

	std::map<int, std::string> getDiffuseTexturesPath() { return m_importer.getDiffuseTexturesPath();  }
	std::map<int, std::string> getNormalsTexturesPath() { return m_importer.getNormalsTexturesPath(); }

protected:
	//ofxAssimpModelLoader m_model;
	MkImporter m_importer;
	std::vector<std::shared_ptr<Mesh>> m_mesh;
	glm::vec3 m_centroid;
	int m_meshCount = 0;
	Material m_material;
	float m_shininess = 1.0f;

	LightsController* m_lightsController = nullptr;

	RT_Box m_box;
	bool m_drawBox = false;

	float getMaxVertexValue() const;
	void setCentroid();
	void scaleMeshes();

	void setPointLightsUniforms(const Camera& camera);
	void setDirectionalLightsUniforms(const Camera& camera);
	void setSpotLightsUniforms(const Camera& camera);

	glm::vec3* m_positions = nullptr;
	glm::vec4* m_diffuseColors = nullptr;
	glm::vec4* m_specularColors = nullptr;
	glm::vec3* m_directions = nullptr;

	float m_tileX = 1.0f;
	float m_tileY = 1.0f;
};