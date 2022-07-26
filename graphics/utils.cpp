#include <cmath>
#include "utils.h"

/**
 *  class Vec3
 */
Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
void Vec3::normalize_() {
    float len = this->length();
    if (len == 0.0f) return;
    this->x /= len;
    this->y /= len;
    this->z /= len;
}
Vec3 Vec3::normalize() const {
    float len = this->length();
    if (len == 0.0f) return Vec3();
    return Vec3(x / len, y / len, z / len);
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
    s = 1 / (float)(s + 1e-8);
    return Vec3(this->x*s, this->y*s, this->z*s);
}
float Vec3::length() const {
    return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
}

/**
 *  class Mat3
 */
std::ostream &operator<<(std::ostream &os, const Mat3 &mat3) {
    os << "Mat3:" << std::endl;
    for (int i = 0; i < 3; ++i) {
        os << "[";
        for (int j = 0; j < 3; ++j) {
            os << mat3.data[i*3+j] << " ";
        }
        os << "]" << std::endl;
    }
    return os;
}
float Mat3::det() const {
    return  data[0]*data[4]*data[8]
            + data[1]*data[5]*data[6]
            + data[2]*data[3]*data[7]
            - data[2]*data[4]*data[6]
            - data[1]*data[3]*data[8]
            - data[0]*data[5]*data[7];
}
Mat3::Mat3(float a, float b, float c, float d, float e, float f, float g, float h, float i) {
    int x = 0;
    this->data[x++] = a;
    this->data[x++] = b;
    this->data[x++] = c;
    this->data[x++] = d;
    this->data[x++] = e;
    this->data[x++] = f;
    this->data[x++] = g;
    this->data[x++] = h;
    this->data[x++] = i;
}

/**
 *  class Color
 */
Color::Color(float r, float g, float b) : r(r), g(g), b(b) {}
void Color::multiply_(float s) {
    r = min(r * s, 1.0f);
    g = min(g * s, 1.0f);
    b = min(b * s, 1.0f);
}
Color Color::multiply(float s) const {
    return Color(min(r*s, 1.0f), min(g*s, 1.0f), min(b*s, 1.0f));
}
Color Color::mix(const Color& color) const {
    return Color(r*color.r, g*color.g, b*color.b);
}
void Color::mix_(const Color& color) {
    this->r *= color.r;
    this->g *= color.g;
    this->b *= color.b;
}
void Color::add_(const Color& color) {
    r = min(r + color.r, 1.0f);
    g = min(g + color.g, 1.0f);
    b = min(b + color.b, 1.0f);
}
void Color::to256(int *out_r, int *out_g, int *out_b) const {
    *out_r = (int) (r * 255);
    *out_g = (int) (g * 255);
    *out_b = (int) (b * 255);
}

std::ostream &operator<<(std::ostream &os, const Color &color) {
    os << "Color(" << color.r << ", " << color.g << ", " << color.b << ")";
    return os;
}

/**
 *  class Ray
 */
Ray::Ray(const Vec3 &origin, const Vec3 &direction) : origin(origin), direction(direction) {}
Vec3 Ray::evaluate(float t) const {
    return this->origin.add(this->direction.multiply(t));
}
