#pragma once
#include "RT_Material.h"
#include "RT_Texture.h"

class DiffuseLight : public RT_Material {
public:
    DiffuseLight(color c) : emit(make_shared<SolidColor>(c)) {}

    virtual bool scatter(
        const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered
    ) const override {
        return false;
    }

    virtual color emitted(double u, double v, const point3& p) const override {
        return emit->value(u, v, p);
    }

public:
    shared_ptr<RT_Texture> emit;
};
