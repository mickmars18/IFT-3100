#pragma once
#include <vector>
#include "RT_Triangle.h"
#include "../Helper/MkImporter.h"
#include "../Domain/Material.h"
#include "../Domain/Transform.h"

class RT_Model {
public:
	RT_Model() {}
	void loadModel(const std::string& filename) {
		m_mesh = m_importer.loadModel(filename);
		m_meshCount = m_mesh.size();

		for (size_t i = 0; i < m_meshCount; i++) {
			ofMaterial material = m_importer.getMaterialForMesh(i);
			ofFloatColor diffuseColor = material.getDiffuseColor();
			color col(diffuseColor.r, diffuseColor.g, diffuseColor.b);
			shared_ptr<RT_Material> mat = make_shared<Lambertian>(col);
			addRT_Triangles(m_mesh[i], mat);
		}
	}

	void setPosition(float x, float y, float z) {
		m_transform.setPosition(x, y, z);
	}

	void setScale(float scale) {
		m_transform.setScale(scale, scale, scale);
	}

	void setRotation(float x, float y, float z) {
		m_transform.setRotationX(x);
		m_transform.setRotationY(y);
		m_transform.setRotationZ(z);
	}

	void addRT_Triangles(std::shared_ptr<Mesh> mesh, shared_ptr<RT_Material> mat) {
		m_transform.getModel();

		std::vector<ofIndexType> indices = mesh->getIndices();
		for (size_t i = 0; i < indices.size(); i += 3) {
			ofDefaultVertexType vertex1 = mesh->getVertex(indices[i]);
			ofDefaultVertexType vertex2 = mesh->getVertex(indices[i+1]);
			ofDefaultVertexType vertex3 = mesh->getVertex(indices[i+2]);

			vec3 p1(vertex1.x, vertex1.y, vertex1.z);
			vec3 p2(vertex2.x, vertex2.y, vertex2.z);
			vec3 p3(vertex3.x, vertex3.y, vertex3.z);
			RT_Triangle triangle();

			m_triangles.push_back(RT_Triangle(p1, p2, p3, mat));
		}
	}

	std::vector<RT_Triangle> getTriangles() {
		std::vector<RT_Triangle> triangles;
		for (size_t i = 0; i < m_triangles.size(); i++) {
			vec3 p1 = m_triangles[i].getPoint(0);
			vec3 p2 = m_triangles[i].getPoint(1);
			vec3 p3 = m_triangles[i].getPoint(2);
			glm::vec3 p1Transformed = glm::vec3(m_transform.getModel() * glm::vec4(p1.x(), p1.y(), p1.z(), 1.0f));
			glm::vec3 p2Transformed = glm::vec3(m_transform.getModel() * glm::vec4(p2.x(), p2.y(), p2.z(), 1.0f));
			glm::vec3 p3Transformed = glm::vec3(m_transform.getModel() * glm::vec4(p3.x(), p3.y(), p3.z(), 1.0f));
			
			vec3 finalp1 = vec3(p1Transformed.x, p1Transformed.y, p1Transformed.z);
			vec3 finalp2 = vec3(p2Transformed.x, p2Transformed.y, p2Transformed.z);
			vec3 finalp3 = vec3(p3Transformed.x, p3Transformed.y, p3Transformed.z);
			triangles.push_back(RT_Triangle(finalp1, finalp2, finalp3, m_triangles[i].getMaterial()));
		}
		return triangles;
	}

private:
	std::vector<RT_Triangle> m_triangles;
	MkImporter m_importer;

	Transform m_transform;

	std::vector<std::shared_ptr<Mesh>> m_mesh;
	int m_meshCount = 0;
};