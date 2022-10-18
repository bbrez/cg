#ifndef __SPHERE_H__
#define __SPHERE_H__
#include "Shape.h"
#include <corecrt_math.h>

class Sphere : public Shape {
public:

    float radius;

    Sphere() = delete;

    Sphere(vf3d origin, olc::Pixel fill, float radius) : Shape(origin, fill), radius(radius) {}

    std::optional<float> intersection(ray r) const override {
        vf3d oc = r.origin - origin;
        float a = r.direction * r.direction;
        float b = 2.0f * (oc * r.direction);
        float c = (oc * oc) - (radius * radius);
        float discriminant = powf(b, 2) - 4 * a * c;
        if (discriminant < 0) { return {}; }
        auto ret = (-b - sqrtf(discriminant) / (2.0f * a));
        if (ret < 0) return {};
        return ret;
    }
};

#endif