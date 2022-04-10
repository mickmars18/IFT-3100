#pragma once

#include "rtweekend.h"

#include "RT_Plane.h"
#include "HittableList.h"
#include "../Domain/Transform.h"

class RTBox : public Hittable {
public:
    RTBox() {}
    RTBox(const point3& p0, const point3& p1, shared_ptr<RT_Material> ptr, Transform& transform) :
        m_ptr(ptr),
        m_point1(p0.x(), p0.y(), p0.z()),
        m_point2(p0.x(), p1.y(), p0.z()),
        m_point3(p1.x(), p1.y(), p0.z()),
        m_point4(p1.x(), p0.y(), p0.z()),
        m_point5(p0.x(), p0.y(), p1.z()),
        m_point6(p0.x(), p1.y(), p1.z()),
        m_point7(p1.x(), p1.y(), p1.z()),
        m_point8(p1.x(), p0.y(), p1.z())
    {
        box_min = p0;
        box_max = p1;

        glm::vec4 glmpoint1 = transform.getModel() * glm::vec4(m_point1.x(), m_point1.y(), m_point1.z(), 1.0f);
        glm::vec4 glmpoint2 = transform.getModel() * glm::vec4(m_point2.x(), m_point2.y(), m_point2.z(), 1.0f);
        glm::vec4 glmpoint3 = transform.getModel() * glm::vec4(m_point3.x(), m_point3.y(), m_point3.z(), 1.0f);
        glm::vec4 glmpoint4 = transform.getModel() * glm::vec4(m_point4.x(), m_point4.y(), m_point4.z(), 1.0f);
        glm::vec4 glmpoint5 = transform.getModel() * glm::vec4(m_point5.x(), m_point5.y(), m_point5.z(), 1.0f);
        glm::vec4 glmpoint6 = transform.getModel() * glm::vec4(m_point6.x(), m_point6.y(), m_point6.z(), 1.0f);
        glm::vec4 glmpoint7 = transform.getModel() * glm::vec4(m_point7.x(), m_point7.y(), m_point7.z(), 1.0f);
        glm::vec4 glmpoint8 = transform.getModel() * glm::vec4(m_point8.x(), m_point8.y(), m_point8.z(), 1.0f);

        vec3 point1(glmpoint1.x, glmpoint1.y, glmpoint1.z);
        vec3 point2(glmpoint2.x, glmpoint2.y, glmpoint2.z);
        vec3 point3(glmpoint3.x, glmpoint3.y, glmpoint3.z);
        vec3 point4(glmpoint4.x, glmpoint4.y, glmpoint4.z);
        vec3 point5(glmpoint5.x, glmpoint5.y, glmpoint5.z);
        vec3 point6(glmpoint6.x, glmpoint6.y, glmpoint6.z);
        vec3 point7(glmpoint7.x, glmpoint7.y, glmpoint7.z);
        vec3 point8(glmpoint8.x, glmpoint8.y, glmpoint8.z);

        sides.add(make_shared<RT_Plane>(point1, point2, point3, point4, ptr));
        sides.add(make_shared<RT_Plane>(point5, point6, point2, point1, ptr));
        sides.add(make_shared<RT_Plane>(point8, point7, point6, point5, ptr));
        sides.add(make_shared<RT_Plane>(point4, point3, point7, point8, ptr));
        sides.add(make_shared<RT_Plane>(point5, point1, point4, point8, ptr));
        sides.add(make_shared<RT_Plane>(point2, point6, point7, point3, ptr));
    }

    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
        return sides.hit(r, t_min, t_max, rec);
    }

    virtual bool bounding_box(double time0, double time1, AABB& output_box) const override {
        output_box = AABB(box_min, box_max);
        return true;
    }

public:
    point3 box_min;
    point3 box_max;
    HittableList sides;

    shared_ptr<RT_Material> m_ptr;

    vec3 m_point1;
    vec3 m_point2;
    vec3 m_point3;
    vec3 m_point4;
    vec3 m_point5;
    vec3 m_point6;
    vec3 m_point7;
    vec3 m_point8;

};
