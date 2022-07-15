#include "geometry.h"
#include <cmath>

Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

void Vec3::normalize_() {
    float len = sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
    this->x /= len;
    this->y /= len;
    this->z /= len;
}

float Vec3::dot(const Vec3 &vec3) const {
    return this->x*vec3.x + this->y*vec3.y + this->z*vec3.z;
}

Vec3 Vec3::add(const Vec3 &vec3) const {
    return Vec3(this->x+vec3.x, this->y+vec3.y, this->z+vec3.z);
}

Vec3 Vec3::multiply(float s) const {
    return Vec3(this->x*s, this->y*s, this->z*s);
}

void Vec3::multiply_(float s) {
    this->x *= s;
    this->y *= s;
    this->z *= s;
}

Vec3 Vec3::cross(const Vec3 &vec3) const {
//    (y1z2 - y2z1, x2z1-z2x1, x1y2 -x2y1)
    return Vec3(
            this->y*vec3.z - vec3.y*this->z,
            vec3.x*this->z - vec3.z*this->x,
            this->x*vec3.y - vec3.x*this->y);
}

std::ostream &operator<<(std::ostream &os, const Vec3 &vec3) {
    os << "Vec3(" << vec3.x << ", " << vec3.y << ", " << vec3.z << ")";
    return os;
}

Vec3 Vec3::sub(const Vec3 &vec3) const {
    return Vec3(this->x-vec3.x, this->y-vec3.y, this->z-vec3.z);
}

Vec3 Vec3::divide(float s) const {
    s = 1 / s;
    return Vec3(this->x*s, this->y*s, this->z*s);
}


Ray::Ray(const Vec3 &origin, const Vec3 &direction) : origin(origin), direction(direction) {}

Vec3 Ray::evaluate(float t) const {
    return this->origin.add(this->direction.multiply(t));
}

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

//void Camera::rasterDeepImage(Byte *pFrameBuffer, std::vector<Surface*> &geometries) const {
//    int i = 0;
//    Ray viewing_ray;
//    for (int y = 0; y < height; ++y) {
//        for (int x = 0; x < width; ++x) {
//            generateViewingRay(x, y, &viewing_ray);
//            float t = Surface::noHit;
//            for (const auto &geometry: geometries) {
//                t = std::min(std::max(geometry->intersect(viewing_ray), 0.0f), t);
//            }
//            if (t != Surface::noHit) {
//                pFrameBuffer[i  ] = 255 - (int)t*10;
//                pFrameBuffer[i+1] = 255 - (int)t*10;
//                pFrameBuffer[i+2] = 255 - (int)t*10;
//                pFrameBuffer[i+3] = 0;
//            }
//            i += 4;
//        }
//    }
//}

void Camera::rasterDeepImage(Byte *pFrameBuffer, std::vector<Surface*> &surfaces) const {
    int i = 0;
    Ray viewing_ray;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            generateViewingRay(x, y, &viewing_ray);
            float t = Surface::noHit;
            HitRecord hitRecord;
            for (const auto &surface: surfaces) {
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





Sphere::Sphere(const Vec3 &center, float radius) : center(center), radius(radius) {}

float Sphere::intersect(const Ray &ray) const {
    Vec3 e_sub_c = ray.origin.sub(center);
    float d_dot_d = ray.direction.dot(ray.direction);
    float tmp = ray.direction.dot(e_sub_c);
    float delta = tmp*tmp - d_dot_d*(e_sub_c.dot(e_sub_c) - radius*radius);
    if (delta < 0) return Surface::noHit;
    return (-tmp - sqrtf(delta)) / d_dot_d;
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

HitRecord::HitRecord(Surface *surface, float t, const Vec3 &normal) : surface(surface), t(t), normal(normal) {}
