#include "Delaunay.h"

Delaunay::Delaunay() {
	m_name = "Delaunay";
    m_shader.load("shaders/model_diffuse_330_vs.glsl", "shaders/model_diffuse_330_fs.glsl");

    m_material.setNumberOfMeshes(1);
    m_material.setDiffuseColor(0, glm::vec3(0.5f));

    setPosition(-445, -243, 0);
}

Delaunay::~Delaunay() {

}

std::string Delaunay::getClassName() {
	return "Delaunay";
}

void Delaunay::setPoints(const std::vector<glm::vec2>& points) {
	m_points.clear();
    m_triangles.clear();
	m_points = points;

	Triangle superTriangle;
    superTriangle.p1 = glm::vec2(-1, -1);
    superTriangle.p2 = glm::vec2(-1, 10000);
    superTriangle.p3 = glm::vec2(10000, -1);
	m_triangles.push_back(superTriangle);

    for (int i = 0; i < m_points.size(); i++) {
        std::vector<Triangle> badTriangles;
        for (int j = 0; j < m_triangles.size(); j++) {
            bool insideTriangle = CircumCircle(m_points[i], m_triangles[j]);
            if (insideTriangle) {
                badTriangles.push_back(m_triangles[j]);
            }
        }

        std::vector<std::pair<Edge, bool>> polygon;
        
        for (size_t j = 0; j < badTriangles.size(); j++) {

            Edge edge1(badTriangles[j].p1, badTriangles[j].p2);
            Edge edge2(badTriangles[j].p2, badTriangles[j].p3);
            Edge edge3(badTriangles[j].p1, badTriangles[j].p3);

            addEdgeToPolygon(edge1, polygon);
            addEdgeToPolygon(edge2, polygon);
            addEdgeToPolygon(edge3, polygon);
        }

        for (size_t j = 0; j < badTriangles.size(); j++) {
            for (size_t k = 0; k < m_triangles.size(); k++) {
                if (badTriangles[j] == m_triangles[k]) {
                    m_triangles.erase(m_triangles.begin() + k);
                    break;
                }
            }
        }

        for (size_t j = 0; j < polygon.size(); j++) {
            if (polygon[j].second)
                continue;

            Triangle newTriangle;
            newTriangle.p1 = polygon[j].first.p1;
            newTriangle.p2 = polygon[j].first.p2;
            newTriangle.p3 = m_points[i];
            m_triangles.push_back(newTriangle);
        }
    }
    for (size_t i = 0; i < m_triangles.size(); i++) {
        if (m_triangles[i].contains(superTriangle.p1) ||
            m_triangles[i].contains(superTriangle.p2) ||
            m_triangles[i].contains(superTriangle.p3)) {

            m_triangles.erase(m_triangles.begin() + i);
            i--;
        }
    }

    generateMeshes();
}

void Delaunay::generateMeshes() {

    m_material.setNumberOfMeshes(m_triangles.size());

    m_mesh.clear();
    
    ofDefaultVertexType vertex;
    vertex.z = 0;
    ofIndexType index;
    for (size_t i = 0; i < m_triangles.size(); i++) {
        std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
        ofDefaultVertexType vertex;

        vertex.x = m_triangles[i].p1.x;
        vertex.y = m_triangles[i].p1.y;
        mesh->addVertex(vertex);

        vertex.x = m_triangles[i].p2.x;
        vertex.y = m_triangles[i].p2.y;
        mesh->addVertex(vertex);

        vertex.x = m_triangles[i].p3.x;
        vertex.y = m_triangles[i].p3.y;
        mesh->addVertex(vertex);

        mesh->addIndex(0);
        mesh->addIndex(1);
        mesh->addIndex(2);

        m_mesh.push_back(mesh);

        if (m_colorMode) {
            float red = ofRandom(0, 1);
            float green = ofRandom(0, 1);
            float blue = ofRandom(0, 1);
            m_material.setDiffuseColor(i, glm::vec3(red, green, blue));
        }
        else {
            m_material.setDiffuseColor(i, glm::vec3(ofRandom(0, 1)));
        }
    }

    m_meshCount = m_mesh.size();
}

void Delaunay::addEdgeToPolygon(const Edge& edge, std::vector<std::pair<Edge, bool>>& polygon) {
    for (size_t i = 0; i < polygon.size(); i++) {
        if (edge == polygon[i].first) {
            polygon[i].second = true;
            return;
        }

    }
    polygon.push_back(std::make_pair(edge, false));
}

int Delaunay::CircumCircle(const glm::vec2& point, const Triangle& triangle) {
    double m1, m2, mx1, mx2, my1, my2;
    double dx, dy, rsqr, drsqr;
    double xc, yc, r;

    const double EPSILON = 0.000001;

    double xp = point.x;
    double yp = point.y;

    double x1 = triangle.p1.x;
    double y1 = triangle.p1.y;
    double x2 = triangle.p2.x;
    double y2 = triangle.p2.y;
    double x3 = triangle.p3.x;
    double y3 = triangle.p3.y;

    /* Check for coincident points */
    if (abs(y1 - y2) < EPSILON && abs(y2 - y3) < EPSILON)
        return(false);
    if (abs(y2 - y1) < EPSILON) {
        m2 = -(x3 - x2) / (y3 - y2);
        mx2 = (x2 + x3) / 2.0;
        my2 = (y2 + y3) / 2.0;
        xc = (x2 + x1) / 2.0;
        yc = m2 * (xc - mx2) + my2;
    }
    else if (abs(y3 - y2) < EPSILON) {
        m1 = -(x2 - x1) / (y2 - y1);
        mx1 = (x1 + x2) / 2.0;
        my1 = (y1 + y2) / 2.0;
        xc = (x3 + x2) / 2.0;
        yc = m1 * (xc - mx1) + my1;
    }
    else {
        m1 = -(x2 - x1) / (y2 - y1);
        m2 = -(x3 - x2) / (y3 - y2);
        mx1 = (x1 + x2) / 2.0;
        mx2 = (x2 + x3) / 2.0;
        my1 = (y1 + y2) / 2.0;
        my2 = (y2 + y3) / 2.0;
        xc = (m1 * mx1 - m2 * mx2 + my2 - my1) / (m1 - m2);
        yc = m1 * (xc - mx1) + my1;
    }
    dx = x2 - xc;
    dy = y2 - yc;
    rsqr = dx * dx + dy * dy;
    dx = xp - xc;
    dy = yp - yc;
    drsqr = dx * dx + dy * dy;
    return((drsqr <= rsqr) ? true : false);
}

void Delaunay::update() {

}