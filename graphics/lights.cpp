#include "lights.h"
#include "common.h"
/**
 *  class Point Light
 */
PointLight::PointLight(const Color &i, const Vec3 &p) : I(i), p(p) {}
Color PointLight::illuminate(const Ray &ray, const HitRecord &hitRecord) const {
    Vec3 x = ray.evaluate(hitRecord.t);
    Vec3 l = p.sub(x);
    float r = l.length();
    l.normalize_();
    Color E = I.multiply(max(0, hitRecord.normal.dot(l)) * (float)1e4 / (r*r));
//    Color E = I.multiply(max(0, hitRecord.normal.dot(l)));
    Color k = hitRecord.surface->material->evaluate(l, ray.direction, hitRecord.normal);
    return k.mix(E);
}

Color PointLight::illuminate(const Ray &ray, const HitRecord &hitRecord, const Scene &scene) const {
    Vec3 x = ray.evaluate(hitRecord.t);
    Vec3 l = p.sub(x);
    float r = l.length();
    l.normalize_();
// Shadow Test
    HitRecord sRec;
    scene.hit(Ray(x, l), 1e-8, Surface::noHit, sRec);
    if (sRec.t != Surface::noHit) return Color();
    Color E = I.multiply(max(0, hitRecord.normal.dot(l)) * (float)1e4 / (r*r));
//    Color E = I.multiply(max(0, hitRecord.normal.dot(l)));
    Color k = hitRecord.surface->material->evaluate(l, ray.direction, hitRecord.normal);
    return k.mix(E);
}

/**
 *
 *  class Ambient Light
 */
AmbientLight::AmbientLight(const Color &i) : I(i) {}
Color AmbientLight::illuminate(const Ray &ray, const HitRecord &hitRecord) const {
    return this->I;
}

Color AmbientLight::illuminate(const Ray &ray, const HitRecord &hitRecord, const Scene &scene) const {
    return this->I;
}
