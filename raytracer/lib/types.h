#ifndef __TYPES_H__
#define __TYPES_H__

struct vf3d {
    vf3d() = default;

    constexpr vf3d(float x, float y, float z) : x(x), y(y), z(z) {}

    constexpr vf3d(float f) : x(f), y(f), z(f) {}

    const float operator*(const vf3d right) const {
        return (x * right.x) + (y * right.y) + (z * right.z);
    }

    const vf3d operator-(const vf3d right) const { return {x - right.x, y - right.y, z - right.z}; }

    float x, y, z;
};

struct ray {
    vf3d origin, direction;

    ray() = default;

    constexpr ray(const vf3d origin, const vf3d direction) : origin(origin), direction(direction) {}
};

#endif