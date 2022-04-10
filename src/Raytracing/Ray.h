#pragma once
#include "vec3.h"

class Ray {
public:
	Ray() {}
	Ray(const point3& origin, const vec3& direction, double time = 0.0)
		: m_origin(origin), m_direction(direction), m_time(time)
	{}

	point3 origin() const { return m_origin; }
	vec3 direction() const { return m_direction; }
	double time() const { return m_time; }

	point3 at(double t) const {
		return m_origin + t * m_direction;
	}
private:
	point3 m_origin;
	vec3 m_direction;
	double m_time;
};
