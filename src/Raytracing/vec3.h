#pragma once
#include <cmath>
#include <ostream>

inline double random_double();
inline double random_double(double min, double max);

inline double clampDouble(double x, double min, double max) {
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

class vec3 {
public:
	vec3() {
		vec[0] = 0.0;
		vec[1] = 0.0;
		vec[2] = 0.0;
	}

	vec3(double x, double y, double z) {
		vec[0] = x;
		vec[1] = y;
		vec[2] = z;
	}

	double x() const { return vec[0]; }
	double y() const { return vec[1]; }
	double z() const { return vec[2]; }

	void set(double x, double y, double z) { 
		vec[0] = x;
		vec[1] = y;
		vec[2] = z;
	}

	vec3 operator-() const { return vec3(-vec[0], -vec[1], -vec[2]); }
	double operator[](int i) const { return vec[i]; }
	double& operator[](int i) { return vec[i]; }

	vec3& operator+=(const vec3& v) {
		vec[0] += v.vec[0];
		vec[1] += v.vec[1];
		vec[2] += v.vec[2];
		return *this;
	}

	vec3& operator*=(const double t) {
		vec[0] *= t;
		vec[1] *= t;
		vec[2] *= t;
		return *this;
	}

	vec3& operator/=(const double t) {
		vec[0] /= t;
		vec[1] /= t;
		vec[2] /= t;
		return *this;
	}

	inline vec3 operator%(const vec3& rhs)
	{
		return vec3(vec[1] * rhs.vec[2] - vec[2] * rhs.vec[1],
			vec[2] * rhs.vec[0] - vec[0] * rhs.vec[2],
			vec[0] * rhs.vec[1] - vec[1] * rhs.vec[0]);
	}

	double length() const {
		return sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
	}

	double length_squared() const {
		return vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2];
	}

	vec3 normalize() const {
		double length = this->length();
		return vec3(vec[0] / length, vec[1] / length, vec[2] / length);
	}

	void clamp(double min, double max) {
		vec[0] = clampDouble(vec[0], min, max);
		vec[1] = clampDouble(vec[1], min, max);
		vec[2] = clampDouble(vec[2], min, max);
	}

	inline static vec3 random() {
		return vec3(random_double(), random_double(), random_double());
	}

	inline static vec3 random(double min, double max) {
		return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
	}

	bool near_zero() const {
		// Return true if the vector is close to zero in all dimensions.
		const auto s = 1e-8;
		return (fabs(vec[0]) < s) && (fabs(vec[1]) < s) && (fabs(vec[2]) < s);
	}

public:
	double vec[3];
};

// Type aliases for vec3
using point3 = vec3;   // 3D point
using color = vec3;    // RGB color


inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
	return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

inline vec3 operator+(const vec3& u, const vec3& v) {
	return vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

inline vec3 operator-(const vec3& u, const vec3& v) {
	return vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

inline vec3 operator*(const vec3& u, const vec3& v) {
	return vec3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

inline vec3 operator*(double t, const vec3& v) {
	return vec3(t * v.x(), t * v.y(), t * v.z());
}

inline vec3 operator*(const vec3& v, double t) {
	return t * v;
}

inline vec3 operator/(vec3 v, double t) {
	return (1 / t) * v;
}

inline double dot(const vec3& u, const vec3& v) {
	return u.x() * v.x()
		+ u.y() * v.y()
		+ u.z() * v.z();
}

inline vec3 cross(const vec3& u, const vec3& v) {
	return vec3(u.y() * v.z() - u.z() * v.y(),
		u.z() * v.x() - u.x() * v.z(),
		u.x() * v.y() - u.y() * v.x());
}

inline vec3 random_in_unit_sphere() {
	while (true) {
		auto p = vec3::random(-1, 1);
		if (p.length_squared() >= 1) continue;
		return p;
	}
}

inline vec3 random_unit_vector() {
	return random_in_unit_sphere().normalize();
}

inline vec3 random_in_hemisphere(const vec3& normal) {
	vec3 in_unit_sphere = random_in_unit_sphere();
	if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
		return in_unit_sphere;
	else
		return -in_unit_sphere;
}

inline vec3 random_in_unit_disk() {
	while (true) {
		auto p = vec3(random_double(-1, 1), random_double(-1, 1), 0);
		if (p.length_squared() >= 1) continue;
		return p;
	}
}

inline vec3 reflect(const vec3& v, const vec3& n) {
	return v - 2 * dot(v, n) * n;
}

inline vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
	auto cos_theta = fmin(dot(-uv, n), 1.0);
	vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
	vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
	return r_out_perp + r_out_parallel;
}




