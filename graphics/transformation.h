#ifndef RENDER_TRANSFORMATION_H
#define RENDER_TRANSFORMATION_H

#include <iostream>
#include <cmath>
#include <cstdlib>
#include "utils.h"

class Vec4 {
public:
    float x, y, z, w;
    explicit Vec4(float x = 0, float y = 0, float z = 0, float w = 1.0f);
    Vec4 add(const Vec4& vec4) const;
};

class Mat4 {
public:
    float data[4][4] = {0};
    void setIdentity_();
    void setZero_();
    Mat4 dotM(const Mat4& mat4) const;
    Vec4 dotV(const Vec4& vec4) const;
    Mat4 operator*(const Mat4& mat4) const;
    Vec4 operator*(const Vec4& vec4) const;
    friend std::ostream &operator<<(std::ostream &os, const Mat4 &mat4);
};

class Transformation {
public:
    static Mat4 scale(float sx, float sy, float sz);
    static Mat4 transform(float tx, float ty, float tz);
    static Mat4 rotateX(float degree);
    static Mat4 rotateY(float degree);
    static Mat4 rotateZ(float degree);
};

class Viewing {
public:
    static void orthoProject(Mat4& mat4,
                             float l, float r,
                             float b, float t,
                             float f, float n);
    static void viewport(Mat4& mat4, int width, int height);
};

// line segment
class LineSeg {
public:
    Vec4 from;
    Vec4 to;
    LineSeg(const Vec4 &from, const Vec4 &to);
    void transform(const Mat4& mat4);
    void render(Byte* pFrameBuffer, int width, int height) const;
};

class WireFrame {
public:
    LineSeg* lines = nullptr;
    int size = 0;   // nums of lines
    void transform(const Mat4& mat4) const;
    void render(Byte* pFrameBuffer, int width, int height) const;
    void show() const;
};

class CubeFrame: public WireFrame {
public:
    CubeFrame(const Vec4 &center, float width);
    ~CubeFrame();
};

#endif //RENDER_TRANSFORMATION_H
