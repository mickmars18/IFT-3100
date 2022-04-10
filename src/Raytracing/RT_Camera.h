#pragma once

#include "rtweekend.h"

class RT_Camera {
public:
    RT_Camera() {
        auto theta = degrees_to_radians(60.0f);
        auto h = tan(theta / 2);
        auto viewport_height = 2.0 * h;
        auto viewport_width = 1.0f * viewport_height;

        w = (vec3(13, 2, 3) -vec3(0, 0, 0)).normalize();
        u = (cross(vec3(0, 1, 0), w)).normalize();
        v = cross(w, u);

        origin = vec3(13, 2, 3);
        horizontal = 10.0 * viewport_width * u;
        vertical = 10.0 * viewport_height * v;
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - 10.0 * w;

        lens_radius = 0.0 / 2;

        time0 = 0.0;
        time1 = 1.0;
    }
    RT_Camera(
        point3 lookfrom,
        point3 lookat,
        vec3   vup,
        double vfov, // vertical field-of-view in degrees
        double aspect_ratio,
        double aperture,
        double focus_dist,
        double _time0 = 0,
        double _time1 = 0
    ) {
        auto theta = degrees_to_radians(vfov);
        auto h = tan(theta / 2);
        auto viewport_height = 2.0 * h;
        auto viewport_width = aspect_ratio * viewport_height;

        w = (lookfrom - lookat).normalize();
        u = (cross(vup, w)).normalize();
        v = cross(w, u);

        origin = lookfrom;
        horizontal = focus_dist * viewport_width * u;
        vertical = focus_dist * viewport_height * v;
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - focus_dist * w;

        lens_radius = aperture / 2;

        time0 = _time0;
        time1 = _time1;
    }

    void setValues(point3 lookfrom, point3 lookat, vec3   vup, double vfov, // vertical field-of-view in degrees
                double aspect_ratio, double aperture, double focus_dist, double _time0 = 0, double _time1 = 0) {
        auto theta = degrees_to_radians(vfov);
        auto h = tan(theta / 2);
        auto viewport_height = 2.0 * h;
        auto viewport_width = aspect_ratio * viewport_height;

        w = (lookfrom - lookat).normalize();
        u = (cross(vup, w)).normalize();
        v = cross(w, u);

        origin = lookfrom;
        horizontal = focus_dist * viewport_width * u;
        vertical = focus_dist * viewport_height * v;
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - focus_dist * w;

        lens_radius = aperture / 2;

        time0 = _time0;
        time1 = _time1;
    }


    Ray get_ray(double s, double t) const {
        vec3 rd = lens_radius * random_in_unit_disk();
        vec3 offset = u * rd.x() + v * rd.y();

        return Ray(
            origin + offset,
            lower_left_corner + s * horizontal + t * vertical - origin - offset,
            random_double(time0, time1)
        );
    }

private:
    point3 origin;
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    double lens_radius;
    double time0, time1;  // shutter open/close times
};
