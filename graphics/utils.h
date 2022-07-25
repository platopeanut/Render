#ifndef RENDER_UTILS_H
#define RENDER_UTILS_H

#include <ostream>
#include <cfloat>
#include <cmath>

inline float max(float x, float y) { return x > y ? x : y; }
inline float min(float x, float y) { return x < y ? x : y; }
typedef unsigned char Byte;


class Vec3 {
public:
    float x, y, z;
    explicit Vec3(float x=0, float y=0, float z=0);
    void normalize_();
    Vec3 normalize() const;
    float length() const;
    float dot(const Vec3& vec3) const;
    Vec3 cross(const Vec3& vec3) const;
    Vec3 add(const Vec3& vec3) const;
    Vec3 sub(const Vec3& vec3) const;
    Vec3 multiply(float s) const;
    void multiply_(float s);
    Vec3 divide(float s) const;

    friend std::ostream &operator<<(std::ostream &os, const Vec3 &vec3);
};

class Mat3 {
public:
    static const int SIZE = 9;
    float data[SIZE] = {0};
    explicit Mat3(float a=0, float b=0, float c=0,
                  float d=0, float e=0, float f=0,
                  float g=0, float h=0, float i=0);
    float det() const;
    friend std::ostream &operator<<(std::ostream &os, const Mat3 &mat3);
};

class Color {
public:
    float r, g, b;  // [0,1]
    explicit Color(float r=0, float g=0, float b=0);
    void multiply_(float s);
    Color multiply(float s) const;
    Color mix(const Color& color) const;
    void add_(const Color& color);
    void to256(int* out_r, int* out_g, int* out_b) const;

    friend std::ostream &operator<<(std::ostream &os, const Color &color);
};

class Ray {
public:
    Vec3 origin;
    Vec3 direction;
    Ray(): origin(Vec3()), direction(Vec3()) {}
    Ray(const Vec3 &origin, const Vec3 &direction);
    Vec3 evaluate(float t) const;
};

#endif //RENDER_UTILS_H
