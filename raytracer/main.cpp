#include <corecrt_math.h>
#include <cstdlib>
#include <optional>
#define OLC_PGE_APPLICATION
#include <memory>

#include "lib/olcPixelGameEngine.h"
#include "lib/types.h"
#include "lib/Shape.h"
#include "lib/Sphere.h"

class RayTracerApp : public olc::PixelGameEngine {
public:

    static constexpr int WIDTH = 250;
    static constexpr int HEIGHT = 250;
    static constexpr int CENTER_X = WIDTH / 2;
    static constexpr int CENTER_Y = HEIGHT / 2;

    RayTracerApp() : FOG(128, 128, 128) {
        this->sAppName = "Ray Tracer";
        shapes.emplace_back(std::make_unique<Sphere>(vf3d(0, 0, 200), olc::GREY, 100));
        shapes.emplace_back(std::make_unique<Sphere>(vf3d(-150, +75, +300), olc::RED, 100));
        shapes.emplace_back(std::make_unique<Sphere>(vf3d(+150, -75, +100), olc::GREEN, 100));
    }

    bool OnUserCreate() override { return true; }

    bool OnUserUpdate(float fElapsedTime) override {
        for (auto y = 0; y < HEIGHT; ++y) {
            for (auto x = 0; x < WIDTH; ++x) {
                auto color = Sample(x - CENTER_X, y - CENTER_Y);
                Draw(x, y, color);
            }
        }
        return true;
    }

private:

    std::vector<std::unique_ptr<Shape>> shapes;
    const olc::Pixel FOG;

    std::optional<olc::Pixel> SampleRay(const ray& r) const {
        olc::Pixel final_color;

        auto intersecter_shape_iterator = shapes.end();
        float intersection_distance = INFINITY;

        for (auto it = shapes.begin(); it != shapes.end(); it++) {
            if (std::optional<float> distance = (*it)->intersection(r).value_or(INFINITY);
                distance < intersection_distance) {
                intersecter_shape_iterator = it;
                intersection_distance = distance.value();
            }
        }

        if (intersecter_shape_iterator == shapes.end()) { return {}; }

        const Shape& intersected_shape = **intersecter_shape_iterator;
        final_color = intersected_shape.sample(r);
        return final_color;
    }

    olc::Pixel Sample(float x, float y) const {
        ray sample_ray({x, y, 0}, {0, 0, 1});
        return SampleRay(sample_ray).value_or(FOG);
    }
};

auto main() -> int {
    RayTracerApp rta;
    if (rta.Construct(RayTracerApp::WIDTH, RayTracerApp::HEIGHT, 1, 1)) { rta.Start(); }
    return 0;
}