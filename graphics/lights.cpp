#include "lights.h"
/**
 *  class Point Light
 */
PointLight::PointLight(const Color &i, const Vec3 &p) : I(i), p(p) {}
Color PointLight::illuminate(const Ray &ray, const HitRecord &hitRecord) {
    Vec3 x = ray.evaluate(hitRecord.t);
    Vec3 l = p.sub(x);
    float r = l.length();
    l.normalize_();
//    Color E = I.multiply(max(0, hitRecord.normal.dot(l)) / (r*r));
    Color E = I.multiply(max(0, hitRecord.normal.dot(l)));
    Color k = hitRecord.surface->material->evaluate(l, ray.direction, hitRecord.normal);
    return k.mix(E);
}

/**
 *
 *  class Ambient Light
 */
AmbientLight::AmbientLight(const Color &i) : I(i) {}
Color AmbientLight::illuminate(const Ray &ray, const HitRecord &hitRecord) {
    return this->I;
}
