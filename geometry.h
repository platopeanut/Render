#ifndef RENDER_GEOMETRY_H
#define RENDER_GEOMETRY_H

#include <ostream>
#include <cfloat>
#include <vector>
typedef unsigned char Byte;

class Vec3 {
public:
    float x, y, z;
    explicit Vec3(float x=0, float y=0, float z=0);
    void normalize_();
    float dot(const Vec3& vec3) const;
    Vec3 cross(const Vec3& vec3) const;
    Vec3 add(const Vec3& vec3) const;
    Vec3 sub(const Vec3& vec3) const;
    Vec3 multiply(float s) const;
    void multiply_(float s);
    Vec3 divide(float s) const;

    friend std::ostream &operator<<(std::ostream &os, const Vec3 &vec3);
};

class Ray {
public:
    Vec3 origin;
    Vec3 direction;
    Ray(): origin(Vec3()), direction(Vec3()) {}
    Ray(const Vec3 &origin, const Vec3 &direction);
    Vec3 evaluate(float t) const;
};

class HitRecord;
class Surface {
public:
    constexpr static const float noHit = FLT_MAX;
    virtual float intersect(const Ray& ray) const = 0;
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

    Sphere(const Vec3 &center, float radius);
    float intersect(const Ray &ray) const override;

private:
    void hit(const Ray &ray, float t0, float t1, HitRecord &hitRecord) override;
};

class Camera {
public:
    // We assume that the size of the image plane is [-1,1]^2
    constexpr static const float Left = -1;
    constexpr static const float Right = 1;
    constexpr static const float Top = 1;
    constexpr static const float Bottom = -1;
    int width, height;  // Screen Size
    float _near, _far, distance; // distance between viewpoint and image plane
    // eye:viewpoint, view:view direction, up:up direction, right: right direction
    Vec3 eye, view, up, right;
    Camera(const Vec3 &eye, const Vec3 &view, const Vec3 &up, int width, int height, float distance, float near, float far);
    void generateViewingRay(int i, int j, Ray* ray) const;
    void rasterDeepImage(Byte* pFrameBuffer, std::vector<Surface*>& surfaces) const;
};

#endif //RENDER_GEOMETRY_H
