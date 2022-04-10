#pragma once
#include "Hittable.h"
#include "RT_Triangle.h"
#include "HittableList.h"
#include <algorithm>

class RT_Plane : public Hittable {
public:
    RT_Plane() {}

    RT_Plane(const vec3& point1, const vec3& point2, const vec3& point3, const vec3& point4, shared_ptr<RT_Material> mat)
    {
            m_triangles.add(std::make_shared<RT_Triangle>
                (point1, point2, point3, mat));
            m_triangles.add(std::make_shared<RT_Triangle>
                (point1, point3, point4, mat));

            double epsilon = 0.00001;

            m_minX = std::min(point1.x(), std::min(point2.x(), std::min(point3.x(), point4.x()))) - epsilon;
            m_minY = std::min(point1.y(), std::min(point2.y(), std::min(point3.y(), point4.y()))) - epsilon;
            m_minZ = std::min(point1.z(), std::min(point2.z(), std::min(point3.z(), point4.z()))) - epsilon;

            m_maxX = std::max(point1.x(), std::max(point2.x(), std::max(point3.x(), point4.x()))) + epsilon;
            m_maxY = std::max(point1.y(), std::max(point2.y(), std::max(point3.y(), point4.y()))) + epsilon;
            m_maxZ = std::max(point1.z(), std::max(point2.z(), std::max(point3.z(), point4.z()))) + epsilon;
    };

    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
        return m_triangles.hit(r, t_min, t_max, rec);
    }

    virtual bool bounding_box(double time0, double time1, AABB& output_box) const override {
        // The bounding box must have non-zero width in each dimension, so pad the Z
        // dimension a small amount.
        output_box = AABB(point3(m_minX, m_minY, m_minZ), point3(m_maxX, m_maxY, m_maxZ));
        return true;
    }

public:
    HittableList m_triangles;
    double m_minX;
    double m_minY;
    double m_minZ;

    double m_maxX;
    double m_maxY;
    double m_maxZ;
};
