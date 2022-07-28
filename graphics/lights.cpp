#include "lights.h"
#include "common.h"
/**
 *  class Point Light
 */
PointLight::PointLight(const Color &i, const Vec3 &p) : color(i), p(p) {}
Color PointLight::illuminate(const Ray &ray, const HitRecord &hitRecord) const {
    Vec3 x = ray.evaluate(hitRecord.t);
    Vec3 l = p.sub(x);
    float r = l.length();
    l.normalize_();
    Color E = color.multiply(max(0, hitRecord.normal.dot(l)) * intensity / (r * r));
//    Color E = color.multiply(max(0, hitRecord.normal.dot(l)));
    Color k = hitRecord.surface->material->evaluate(l, ray.direction, hitRecord.normal);
    return k.mix(E);
}
// With Shadow Test
Color PointLight::illuminate(const Ray &ray, const HitRecord &hitRecord, const Scene &scene) const {
    Vec3 x = ray.evaluate(hitRecord.t);
    Vec3 l = p.sub(x);
    float r = l.length();
    l.normalize_();
// Shadow Test
    HitRecord sRec;
    scene.hit(Ray(x, l), 0.1, r, sRec);
    if (sRec.t != Surface::noHit) return Color();
    Color E = color.multiply(max(0, hitRecord.normal.dot(l)) * intensity / (r * r));
    Color k = hitRecord.surface->material->evaluate(l, ray.direction, hitRecord.normal);
    return k.mix(E);
}

/**
 *
 *  class Ambient Light
 */
AmbientLight::AmbientLight(const Color &i) : color(i) {}
Color AmbientLight::illuminate(const Ray &ray, const HitRecord &hitRecord) const {
    return this->color.multiply(intensity);
}

Color AmbientLight::illuminate(const Ray &ray, const HitRecord &hitRecord, const Scene &scene) const {
    return this->color.multiply(intensity);
}

/**
 *  class Directional Light
 */
DirectionalLight::DirectionalLight(const Color &color, const Vec3 &d) : color(color), d(d.reverse()) {}

Color DirectionalLight::illuminate(const Ray &ray, const HitRecord &hitRecord) const {
    Color E = color.multiply(max(0, hitRecord.normal.dot(d)) * intensity);
    Color k = hitRecord.surface->material->evaluate(d, ray.direction, hitRecord.normal);
    return k.mix(E);
}

Color DirectionalLight::illuminate(const Ray &ray, const HitRecord &hitRecord, const Scene &scene) const {
    Vec3 x = ray.evaluate(hitRecord.t);
// Shadow Test
    HitRecord sRec;
    scene.hit(Ray(x, d), 0.1, Surface::noHit, sRec);
    if (sRec.t != Surface::noHit) return Color();
    Color E = color.multiply(max(0, hitRecord.normal.dot(d)) * intensity);
    Color k = hitRecord.surface->material->evaluate(d, ray.direction, hitRecord.normal);
    return k.mix(E);
}


