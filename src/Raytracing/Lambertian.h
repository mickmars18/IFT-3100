#pragma once
#include "rtweekend.h"
#include "Hittable.h"
#include "RT_Material.h"
#include "RT_Texture.h"

class Lambertian : public RT_Material {
public:
    Lambertian(const color& a) : albedo(make_shared<SolidColor>(a)) {}
    Lambertian(shared_ptr<RT_Texture> a) : albedo(a) {}

    virtual bool scatter(const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered) const override {
        auto scatter_direction = rec.normal + random_unit_vector();

        // Catch degenerate scatter direction
        if (scatter_direction.near_zero())
            scatter_direction = rec.normal;

        scattered = Ray(rec.p, scatter_direction, r_in.time());
        attenuation = albedo->value(rec.u, rec.v, rec.p);
        return true;
    }

public:
    shared_ptr<RT_Texture> albedo;
};
