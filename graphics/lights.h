#ifndef RENDER_LIGHTS_H
#define RENDER_LIGHTS_H

#include "utils.h"
#include "surfaces.h"

class Light {
public:
    virtual Color illuminate(const Ray& ray, const HitRecord& hitRecord) = 0;
};

class PointLight: Light {
public:
    Color I;    // color of light
    Vec3 p;     // position of light
    PointLight(const Color &i, const Vec3 &p);
    Color illuminate(const Ray &ray, const HitRecord &hitRecord) override;
};

class AmbientLight: Light {
public:
    Color I;
    explicit AmbientLight(const Color &i);
    Color illuminate(const Ray &ray, const HitRecord &hitRecord) override;
};

#endif //RENDER_LIGHTS_H
