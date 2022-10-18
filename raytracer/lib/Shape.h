#ifndef __SHAPE_H__
#define __SHAPE_H__

#include "olcPixelGameEngine.h"
#include "types.h"
#include <optional>

class Shape {
public:

    vf3d origin;
    olc::Pixel fill;

    Shape() = delete;
    virtual ~Shape() = default;

    Shape(vf3d origin, olc::Pixel fill) : origin(origin), fill(fill) {}

    virtual olc::Pixel sample(ray sample_ray) const { return fill; }

    virtual std::optional<float> intersection(ray r) const = 0;
};

#endif