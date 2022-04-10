#pragma once
#include "RT_Material.h"
#include "Hittable.h"
#include "vec3.h"

class Metal : public RT_Material {
public:
    Metal(const color& a) 
        : albedo(a) {}

    virtual bool scatter(
        const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered
    ) const override {
        vec3 reflected = reflect(r_in.direction().normalize(), rec.normal);
        scattered = Ray(rec.p, reflected, r_in.time());
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }

public:
    color albedo;
};
