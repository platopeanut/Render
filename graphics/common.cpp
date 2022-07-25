#include "common.h"

/**
 *  class Camera
 */
Camera::Camera(const Vec3 &eye, const Vec3 &view, const Vec3 &up, int width, int height, float distance, float near, float far)
: eye(eye), view(view), width(width), height(height), distance(distance), _near(near), _far(far) {
    this->right = view.cross(up);
    this->up = this->right.cross(view);
}
void Camera::generateViewingRay(int i, int j, Ray *ray) const {
    float u = Left + (float)((Right-Left)*(i+0.5)/width);
    float v = Bottom + (float)((Top-Bottom)*(j+0.5)/height);
    ray->origin = eye;
    ray->direction = right.multiply(u).add(up.multiply(v)).add(view.multiply(distance));
    ray->direction.normalize_();
}
void Camera::rasterDeepImage(Byte *pFrameBuffer, const Scene& scene) const {
    int i = 0;
    Ray viewing_ray;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            generateViewingRay(x, y, &viewing_ray);
            float t = Surface::noHit;
            HitRecord hitRecord;
            for (const auto &surface: scene.surfaces) {
                surface->hit(viewing_ray, _near, _far, hitRecord);
                if (hitRecord.t < t) t = hitRecord.t;
            }
            if (t != Surface::noHit) {
                pFrameBuffer[i  ] = 255 - (int)((t - _near) / (_far - _near) * 255);
                pFrameBuffer[i+1] = 255 - (int)((t - _near) / (_far - _near) * 255);
                pFrameBuffer[i+2] = 255 - (int)((t - _near) / (_far - _near) * 255);
                pFrameBuffer[i+3] = 0;
            }
            i += 4;
        }
    }
}
void Camera::shadeRay(Byte* pFrameBuffer, const Scene& scene) const {
    int i = 0;
    Ray viewing_ray;
    HitRecord hitRecord;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            generateViewingRay(x, y, &viewing_ray);
            scene.hit(viewing_ray, _near, _far, hitRecord);
            if (hitRecord.t != Surface::noHit) {
                Color c;
                for (const auto &light: scene.lights) {
//                    c.add_(light->illuminate(viewing_ray, hitRecord));
                    c.add_(light->illuminate(viewing_ray, hitRecord, scene));
                }
                int r, g, b;
                c.to256(&r, &g, &b);
                pFrameBuffer[i  ] = b;
                pFrameBuffer[i+1] = g;
                pFrameBuffer[i+2] = r;
                pFrameBuffer[i+3] = 0;
            }
            i += 4;
        }
    }

}

/**
 *  class Scene
 */
void Scene::addSurface(Surface* surface) {
    this->surfaces.push_back(surface);
}
void Scene::addLight(Light *light) {
    this->lights.push_back(light);
}

void Scene::hit(const Ray &ray, float t0, float t1, HitRecord &hitRecord) const {
    HitRecord hitRec;
    hitRecord = hitRec;
    for (const auto &surface: this->surfaces) {
        surface->hit(ray, t0, t1, hitRec);
        if (hitRec.t < hitRecord.t) hitRecord = hitRec;
    }
}
