#include "BezierSurface.h"

std::string ControlPoint::getClassName() {
	return "ControlPoint";
}

void ControlPoint::update() {

}

void ControlPoint::draw(const Window& window, const Camera& camera) {

}

BezierSurface::BezierSurface() {
	m_icosphere = new Icosphere(10.0f, 2);

	m_name = "Bezier Surface";
	m_icosphere->setScale(0.5f);
	m_shader.load("shaders/model_diffuse_330_vs.glsl", "shaders/model_diffuse_330_fs.glsl");
}

std::vector<ControlPoint*> BezierSurface::setup(int pointsPerLine, int nbSubdivision) {
	m_pointsPerLine = pointsPerLine;
	m_subdivision = nbSubdivision;
	int offset = 0;
	for (size_t i = 0; i < nbSubdivision; i++)
	{
		for (size_t j = 0; j < nbSubdivision; j++) {
			m_mesh.addIndex(j + offset);
			m_mesh.addIndex(j + 1 + offset);
			m_mesh.addIndex(j + nbSubdivision + 1 + offset);

			m_mesh.addIndex(j + 1 + offset);
			m_mesh.addIndex(j + nbSubdivision + 2 + offset);
			m_mesh.addIndex(j + nbSubdivision + 1 + offset);
		}
		offset += nbSubdivision + 1;
	}


	for (int i = 0; i < pointsPerLine; i++) {
		for (int j = 0; j < pointsPerLine; j++) {
			ControlPoint* point = new ControlPoint(i, j);
			point->setPositionX(i * 100 - 180);
			point->setPositionZ(j * 100 + 50);
			addControlPoint(point);
		}
	}
	return m_controlPoints;
}

std::string BezierSurface::getClassName() {
	return "BezierSurface";
}

void BezierSurface::update() {

}

glm::vec3 BezierSurface::getPoint(int i, int j) {
	return m_controlPoints[m_pointsPerLine * i + j]->getPosition();
}

void BezierSurface::evaluate() {
	m_evaluatedPoints.clear();
	for (size_t i = 0; i < m_subdivision + 1; i++) {
		for (size_t j = 0; j < m_subdivision + 1; j++) {
			m_evaluatedPoints.push_back(evaluate((float)i / (float)m_subdivision, (float)j / (float)m_subdivision));
		}
	}
}

glm::vec3 BezierSurface::evaluate(float u, float v) {
	glm::vec3 result;
	for (int i = 0; i < m_pointsPerLine; i++)
	{
		for (int j = 0; j < m_pointsPerLine; j++)
		{
			float b0 = B(m_pointsPerLine - 1 - i, m_pointsPerLine - 1, u);
			float b1 = B(m_pointsPerLine - 1 - j, m_pointsPerLine - 1, v);
			glm::vec3 point = getPoint(i, j);
			int x = 0;
			result += b0 * b1 * point;
		}
	}
	
	return result;
}

float BezierSurface::B(int i, int n, float u) {
	return bernsteinPolynomial(n, i) * pow(u, i) * pow((1.0f - u), n - i);
}

int BezierSurface::bernsteinPolynomial(int n, int i) {
	long long N = (long long)n;
	long long I = (long long)i;
	long long result = factorial(N) / (factorial(I) * factorial(N - I));
	return result;
}

long long BezierSurface::factorial(long long n) {
	if (n > 20) {
		std::cout << "max n is 20" << std::endl;
		return -1;
	}
	long long result = 1;
	while (n > 1) {
		result *= n;
		n--;
	}
	return result;
}

void BezierSurface::setNbSubdivision(int subdivision) {
	m_subdivision = subdivision;
	m_evaluatedPoints.reserve(m_controlPoints.size() * pow(subdivision, 2));
}

void BezierSurface::addControlPoint(ControlPoint* point) {
	m_controlPoints.push_back(point);
}

void BezierSurface::draw(const Window& window, const Camera& camera) {
	for (size_t i = 0; i < m_controlPoints.size(); i++) {
		m_icosphere->setPosition(m_controlPoints[i]->getPosition());
		m_icosphere->draw(window, camera);
	}
	evaluate();

	m_mesh.clearVertices();
	ofDefaultVertexType vertex;
	for (size_t i = 0; i < m_evaluatedPoints.size(); i++)
	{
		vertex.x = m_evaluatedPoints[i].x;
		vertex.y = m_evaluatedPoints[i].y;
		vertex.z = m_evaluatedPoints[i].z;
		m_mesh.addVertex(vertex);
	}

	ofEnableDepthTest();
	m_shader.begin();
	m_shader.setUniformMatrix4f("modelview", camera.getViewMatrix() * getModel());
	m_shader.setUniformMatrix4f("projection", camera.getProjection());
	m_shader.setUniform3f("color_diffuse", glm::vec3(0.7f, 0.7f, 0.7f));

	m_mesh.drawWireframe();

	m_shader.end();
	ofDisableDepthTest();
}