#pragma once
#include "Ray.h"
#include "AABB.h"
class RT_Material;

struct HitRecord {
    point3 p;
    vec3 normal;
    shared_ptr<RT_Material> mat_ptr;
    double t;
    double u;
    double v;
    bool front_face;

    inline void set_face_normal(const Ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        if (front_face)
            normal = outward_normal;
        else
            normal = -outward_normal;
    }
};

class Hittable {
public:
    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
    virtual bool bounding_box(double time0, double time1, AABB& output_box) const = 0;
};