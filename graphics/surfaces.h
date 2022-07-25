#ifndef RENDER_SURFACES_H
#define RENDER_SURFACES_H

#include "utils.h"
#include "materials.h"

class HitRecord;

class Surface {
public:
    constexpr static const float noHit = FLT_MAX;
    Material* material = nullptr;
    virtual void hit(const Ray& ray, float t0, float t1, HitRecord& hitRecord) = 0;
};

class HitRecord {
public:
    Surface* surface;   // Surface that was hit
    float t;    // Coordinate of hit point along the ray
    Vec3 normal;    // Surface normal at the hit point
    explicit HitRecord(Surface *surface=nullptr, float t=Surface::noHit, const Vec3 &normal=Vec3());
};

class Sphere: Surface {
public:
    Vec3 center;
    float radius;

    Sphere(const Vec3 &center, float radius, Material* material);
    void hit(const Ray &ray, float t0, float t1, HitRecord &hitRecord) override;
};

class Triangle: Surface {
public:
    Vec3 a, b, c;
    Vec3 normal;
    Triangle(const Vec3 &a, const Vec3 &b, const Vec3 &c, Material* material);
    void hit(const Ray &ray, float t0, float t1, HitRecord &hitRecord) override;
};

#endif //RENDER_SURFACES_H
