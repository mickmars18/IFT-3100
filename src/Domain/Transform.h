#pragma once

#include "ofVec3f.h"
#include "ofMatrix4x4.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include <glm/gtx/quaternion.hpp>
#include "Camera.h"

class Transform {
public:
	Transform();

	glm::mat4 getModel();
	glm::mat4 getMVP(const Camera& camera);

	inline glm::vec3& getPosition() { return m_position; }
	inline glm::vec3& getRotation() { return m_rotation; }
	inline glm::vec3& getScale() { return m_scale; }

	void setOrigin(float x, float y, float z);
	void setOrigin(const glm::vec3& origin);

	inline void setPosition(float x, float y, float z) { m_position = glm::vec3(x, y, z); }
	inline void setScale(float x, float y, float z) { m_scale = glm::vec3(x, y, z); }

	void setRotationX(float angle);
	void setRotationY(float angle);
	void setRotationZ(float angle);
	void addRotationX(float angle);
	void addRotationY(float angle);
	void addRotationZ(float angle);

private:
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;

	glm::mat4 m_origin;

	glm::vec3 m_axisX;
	glm::vec3 m_axisY;
	glm::vec3 m_axisZ;

	float degreeToRadian(float degree) const;
	float radianToDegree(float radian) const;
};