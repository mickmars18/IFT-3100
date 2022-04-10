#include "Transform.h"

Transform::Transform() :
	m_position(glm::vec3()),
	m_scale(glm::vec3(1.0f, 1.0f, 1.0f)),
	m_axisX(glm::vec3(1.0f, 0.0f, 0.0f)),
	m_axisY(glm::vec3(0.0f, 1.0f, 0.0f)),
	m_axisZ(glm::vec3(0.0f, 0.0f, 1.0f)),
	m_rotation(glm::vec3()),
	m_origin(glm::translate(glm::vec3(0.0f, 0.0f, 0.0f)))
{
}


glm::mat4 Transform::getModel() {
	glm::mat4 positionMatrix = glm::translate(getPosition());

	glm::mat4 rotXMatrix = glm::rotate(degreeToRadian(m_rotation.x), m_axisX);
	glm::mat4 rotYMatrix = glm::rotate(degreeToRadian(m_rotation.y), m_axisY);
	glm::mat4 rotZMatrix = glm::rotate(degreeToRadian(m_rotation.z), m_axisZ);
	glm::mat4 rotationMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

	glm::mat4 scaleMatrix = glm::scale(glm::vec3(m_scale.x, m_scale.y, m_scale.z));

	return positionMatrix * rotationMatrix * scaleMatrix * m_origin;
}

void Transform::setOrigin(float x, float y, float z) {
	m_origin = glm::translate(glm::vec3(-x, -y, -z));
}

void Transform::setOrigin(const glm::vec3& origin) {
	m_origin = glm::translate(-origin);
}

glm::mat4 Transform::getMVP(const Camera& camera) {
	glm::mat4 model = getModel();
	glm::mat4 view = camera.getViewMatrix();
	glm::mat4 projection = camera.getProjection();
	return projection * view * model;
}

float Transform::degreeToRadian(float degree) const
{
	float pi = 3.14159265359f;
	return (degree * (pi / 180));
}

float Transform::radianToDegree(float radian) const
{
	float pi = 3.14159265359f;
	return(radian * (180 / pi));
}

void Transform::addRotationX(float angle) {
	m_rotation.x += angle;
}

void Transform::setRotationX(float angle) {
	m_rotation.x = angle;
}

void Transform::addRotationY(float angle) {
	m_rotation.y += angle;
}

void Transform::setRotationY(float angle) {
	m_rotation.y = angle;
}

void Transform::addRotationZ(float angle) {
	m_rotation.z += angle;
}

void Transform::setRotationZ(float angle) {
	m_rotation.z = angle;
}