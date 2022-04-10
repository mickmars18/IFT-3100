#pragma once
#include "rtweekend.h"
#include "RT_Texture.h"

struct HitRecord;

class RT_Material {
public:
    virtual color emitted(double u, double v, const point3& p) const {
        return color(0, 0, 0);
    }
    virtual bool scatter(const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered) const = 0;
};
