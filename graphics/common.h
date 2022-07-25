#ifndef RENDER_COMMON_H
#define RENDER_COMMON_H

#include "utils.h"
#include "surfaces.h"
#include "lights.h"
#include <vector>
#include <iostream>

class Scene {
public:
    std::vector<Surface*> surfaces;
    std::vector<Light*> lights;
    void addSurface(Surface* surface);
    void addLight(Light* light);
    void hit(const Ray& ray, float t0, float t1, HitRecord& hitRecord) const;
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
    Color bgColor = Color((float)135/255,(float)206/255,(float)235/255);
    Camera(const Vec3 &eye, const Vec3 &view, const Vec3 &up, int width, int height, float distance, float near, float far);
    void generateViewingRay(int i, int j, Ray* ray) const;
    void rasterDeepImage(Byte* pFrameBuffer, const Scene& scene) const;
    void shadeRay(Byte* pFrameBuffer, const Scene& scene) const;
};

#endif //RENDER_COMMON_H
