#ifndef RENDER_LIGHTS_H
#define RENDER_LIGHTS_H

#include "utils.h"
#include "surfaces.h"

class Scene;
class Light {
public:
    virtual Color illuminate(const Ray& ray, const HitRecord& hitRecord) const = 0;
    virtual Color illuminate(const Ray& ray, const HitRecord& hitRecord, const Scene& scene) const = 0;
};

/**
 *      E = color * cos_θ / r^2
 */
class PointLight: Light {
public:
    float intensity = 1e2;
    Color color;    // color of light
    Vec3 p;     // position of light
    PointLight(const Color &i, const Vec3 &p);
    Color illuminate(const Ray &ray, const HitRecord &hitRecord) const override;
    Color illuminate(const Ray &ray, const HitRecord &hitRecord, const Scene &scene) const override;
};
/**
 *      E = H * cos_θ
 */
class DirectionalLight: Light {
public:
    float intensity = 1e2;
    Color color;    // color of light
    Vec3 d;     // direction of light
    DirectionalLight(const Color &color, const Vec3 &d);
    Color illuminate(const Ray &ray, const HitRecord &hitRecord) const override;
    Color illuminate(const Ray &ray, const HitRecord &hitRecord, const Scene &scene) const override;
};

class AmbientLight: Light {
public:
    float intensity = 2;
    Color color;
    explicit AmbientLight(const Color &i);
    Color illuminate(const Ray &ray, const HitRecord &hitRecord) const override;
    Color illuminate(const Ray &ray, const HitRecord &hitRecord, const Scene &scene) const override;
};

#endif //RENDER_LIGHTS_H
