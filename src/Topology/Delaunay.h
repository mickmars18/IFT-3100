#pragma once
#include "../Domain/Object.h"
#include "../Models/Model.h"

class Delaunay : public Model {
public:
	struct Triangle {
		glm::vec2 p1;
		glm::vec2 p2;
		glm::vec2 p3;
		bool operator==(const Triangle& triangle) {
			return triangle.p1.x == p1.x && triangle.p1.y == p1.y && 
				triangle.p2.x == p2.x && triangle.p2.y == p2.y &&
				triangle.p3.x == p3.x && triangle.p3.y == p3.y;
		}
		bool contains(const glm::vec2 point) {
			return point.x == p1.x && point.y == p1.y ||
				point.x == p2.x && point.y == p2.y ||
				point.x == p3.x && point.y == p3.y;
		}
	};

	class Edge {
	public:
		Edge(const glm::vec2& point1, const glm::vec2& point2) :
			p1(point1), p2(point2) {}
		glm::vec2 p1;
		glm::vec2 p2;
		bool operator==(const Edge& edge) const {
			return (edge.p1 == p1 && edge.p2 == p2) || (edge.p1 == p2 && edge.p2 == p1);
		}
	};

	Delaunay();
	~Delaunay();

	void setPoints(const std::vector<glm::vec2>& points);
	void generateMeshes();

	std::string getClassName() override;
	void update() override;

	bool getColorMode() const { return m_colorMode; }
	void setColorMode(bool colorMode) { m_colorMode = colorMode; }
private:
	std::vector<glm::vec2> m_points;
	std::vector<Triangle> m_triangles;

	int CircumCircle(const glm::vec2& point, const Triangle& triangle);
	void addEdgeToPolygon(const Edge& edge, std::vector<std::pair<Edge, bool>>& polygon);

	bool m_colorMode = false;
};
