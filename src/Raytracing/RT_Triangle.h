#pragma once
#include "Hittable.h"
#include <algorithm> 

class RT_Triangle : public Hittable {
public:
	RT_Triangle() {}
	RT_Triangle(const vec3& v1, const vec3& v2, const vec3& v3, shared_ptr<RT_Material> material) 
	: m_material(material) {
		m_vertices[0] = v1;
		m_vertices[1] = v2;
		m_vertices[2] = v3;
        setNormal();
	}

    virtual shared_ptr<RT_Material> getMaterial() {
        return m_material;
    }

    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
        const float EPSILON = 0.0000001;
        vec3 edge1, edge2, h, s, q;
        float a, f, u, v;
        edge1 = m_vertices[1] - m_vertices[0];
        edge2 = m_vertices[2] - m_vertices[0];
        h = cross(r.direction(), edge2);
        a = dot(edge1, h);
        if (a > -EPSILON && a < EPSILON)
            return false;    // This ray is parallel to this triangle.
        f = 1.0 / a;
        s = r.origin() - m_vertices[0];
        u = f * dot(s, h);
        if (u < 0.0 || u > 1.0)
            return false;
        q = cross(s, edge1);
        v = f * dot(r.direction(), q);
        if (v < 0.0 || u + v > 1.0)
            return false;
        // At this stage we can compute t to find out where the intersection point is on the line.
        float t = f * dot(edge2, q);
        if (t > EPSILON) // ray intersection
        {
            rec.p = r.origin() + r.direction() * t;
            rec.set_face_normal(r, m_normal);
            rec.mat_ptr = m_material;

            rec.u = u;
            rec.v = v;

            rec.t = t;

            return true;
        }
        else // This means that there is a line intersection but not a ray intersection.
            return false;
    }

    void setNormal() {
        vec3 u = m_vertices[1] - m_vertices[0];
        vec3 v = m_vertices[2] - m_vertices[1];

        double x = u.y() * v.z() - u.z() * v.y();
        double y = u.z() * v.x() - u.x() * v.z();
        double z = u.x() * v.y() - u.y() * v.x();
        vec3 n = vec3(x, y, z).normalize();

        m_normal.set(-n.x(), -n.y(), -n.z());
    }

	virtual bool bounding_box(double time0, double time1, AABB& output_box) const override {
		// The bounding box must have non-zero width in each dimension, so pad the Z
		// dimension a small amount.

		double minX = std::min(m_vertices[0].x(), std::min(m_vertices[1].x(), m_vertices[2].x()));
		double minY = std::min(m_vertices[0].y(), std::min(m_vertices[1].y(), m_vertices[2].y()));
		double minZ = std::min(m_vertices[0].z(), std::min(m_vertices[1].z(), m_vertices[2].z()));

		double maxX = std::max(m_vertices[0].x(), std::max(m_vertices[1].x(), m_vertices[2].x()));
		double maxY = std::max(m_vertices[0].y(), std::max(m_vertices[1].y(), m_vertices[2].y()));
		double maxZ = std::max(m_vertices[0].z(), std::max(m_vertices[1].z(), m_vertices[2].z()));

		output_box = AABB(point3(minX, minY, minZ - 0.0001), point3(maxX, maxY, maxZ + 0.0001));
		return true;
	}

    vec3 getPoint(int i) {
        return m_vertices[i];
    }

private:
	vec3 m_vertices[3];
	shared_ptr<RT_Material> m_material;
    vec3 m_normal;
};

class glmTriangle {
public:
    glm::vec3 p1;
    glm::vec3 p2;
    glm::vec3 p3;
};
