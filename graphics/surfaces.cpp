#include "surfaces.h"

/**
 *  class HitRecord
 */
HitRecord::HitRecord(Surface *surface, float t, const Vec3 &normal) : surface(surface), t(t), normal(normal) {}

/**
 *  class Sphere
 */
Sphere::Sphere(const Vec3 &center, float radius, Material* material)
: center(center), radius(radius) {
    this->material = material;
}
void Sphere::hit(const Ray &ray, float t0, float t1, HitRecord &hitRecord) {
    Vec3 e_sub_c = ray.origin.sub(center);
    float d_dot_d = ray.direction.dot(ray.direction);
    float tmp = ray.direction.dot(e_sub_c);
    float delta = tmp*tmp - d_dot_d*(e_sub_c.dot(e_sub_c) - radius*radius);
    if (delta < 0) {
        hitRecord.t = Surface::noHit;
        hitRecord.surface = nullptr;
        hitRecord.normal = Vec3();
        return;
    }
    float t = (-tmp - sqrtf(delta)) / d_dot_d;
    if (t >= t0 && t <= t1) {
        hitRecord.t = t;
        hitRecord.surface = this;
        hitRecord.normal = ray.origin.add(ray.direction.multiply(t)).sub(center).divide(radius);
        return;
    }
    t = (-tmp + sqrtf(delta)) / d_dot_d;
    if (t >= t0 && t <= t1) {
        hitRecord.t = t;
        hitRecord.surface = this;
        hitRecord.normal = ray.origin.add(ray.direction.multiply(t)).sub(center).divide(radius);
        return;
    }
    hitRecord.t = Surface::noHit;
    hitRecord.surface = nullptr;
    hitRecord.normal = Vec3();
}

/**
 *  class Triangle
 */
Triangle::Triangle(const Vec3 &a, const Vec3 &b, const Vec3 &c, Material* material): a(a), b(b), c(c) {
    this->material = material;
    this->normal = b.sub(a).cross(c.sub(a)).normalize();
}
void Triangle::hit(const Ray &ray, float t0, float t1, HitRecord &hitRecord) {
    Mat3 A(a.x-b.x, a.x-c.x, ray.direction.x,
           a.y-b.y, a.y-c.y, ray.direction.y,
           a.z-b.z, a.z-c.z, ray.direction.z);
    Mat3 Mt(a.x-b.x, a.x-c.x, a.x-ray.origin.x,
            a.y-b.y, a.y-c.y, a.y-ray.origin.y,
            a.z-b.z, a.z-c.z, a.z-ray.origin.z);
    Mat3 Mb(a.x-ray.origin.x, a.x-c.x, ray.direction.x,
            a.y-ray.origin.y, a.y-c.y, ray.direction.y,
            a.z-ray.origin.z, a.z-c.z, ray.direction.z);
    Mat3 My(a.x-b.x, a.x-ray.origin.x, ray.direction.x,
            a.y-b.y, a.y-ray.origin.y, ray.direction.y,
            a.z-b.z, a.z-ray.origin.z, ray.direction.z);

    float A_det = A.det();
    float _t = Mt.det() / A_det;
    if (_t >= t0 && _t <= t1) {
        float _y = My.det() / A_det;
        if (_y >= 0 && _y <= 1) {
            float _b = Mb.det() / A_det;
            if (_b >= 0 && _b <= 1 - _y) {
                hitRecord.t = _t;
                hitRecord.surface = this;
                hitRecord.normal = this->normal;
                return;
            }
        }
    }
    hitRecord.t = Surface::noHit;
    hitRecord.surface = nullptr;
    hitRecord.normal = Vec3();
}