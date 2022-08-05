#include "transformation.h"
#include "../display/win32.h"
#include <assert.h>


/**
 *  class Vec4
 */

Vec4::Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

Vec4 Vec4::add(const Vec4 &vec4) const {
    return Vec4(x + vec4.x, y + vec4.y, z + vec4.z, w + vec4.w);
}

void Vec4::divideW_() {
    if (w != 0) {
        x /= w;
        y /= w;
        z /= w;
        w = 1.0f;
    }
}

/**
 *  class Mat4
 */
void Mat4::setIdentity_() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            data[i][j] = (i == j) ? 1.0f: 0.0f;
        }
    }
}
void Mat4::setZero_() {
    for (auto & i : data)
        for (float & j : i)
            j = 0.0f;
}
Mat4 Mat4::dotM(const Mat4& mat4) const {
    Mat4 result;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            for (int k = 0; k < 4; ++k)
                result.data[i][j] += data[i][k] * mat4.data[k][j];
    return result;
}
Vec4 Mat4::dotV(const Vec4 &vec4) const {
    Vec4 result;
    result.x = data[0][0]*vec4.x + data[0][1]*vec4.y + data[0][2]*vec4.z + data[0][3]*vec4.w;
    result.y = data[1][0]*vec4.x + data[1][1]*vec4.y + data[1][2]*vec4.z + data[1][3]*vec4.w;
    result.z = data[2][0]*vec4.x + data[2][1]*vec4.y + data[2][2]*vec4.z + data[2][3]*vec4.w;
    result.w = data[3][0]*vec4.x + data[3][1]*vec4.y + data[3][2]*vec4.z + data[3][3]*vec4.w;
    return result;
}
Mat4 Mat4::operator*(const Mat4 &mat4) const {
    Mat4 result;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            for (int k = 0; k < 4; ++k)
                result.data[i][j] += data[i][k] * mat4.data[k][j];
    return result;
}
Vec4 Mat4::operator*(const Vec4 &vec4) const {
    Vec4 result;
    result.x = data[0][0]*vec4.x + data[0][1]*vec4.y + data[0][2]*vec4.z + data[0][3]*vec4.w;
    result.y = data[1][0]*vec4.x + data[1][1]*vec4.y + data[1][2]*vec4.z + data[1][3]*vec4.w;
    result.z = data[2][0]*vec4.x + data[2][1]*vec4.y + data[2][2]*vec4.z + data[2][3]*vec4.w;
    result.w = data[3][0]*vec4.x + data[3][1]*vec4.y + data[3][2]*vec4.z + data[3][3]*vec4.w;
    return result;
}
std::ostream &operator<<(std::ostream &os, const Mat4 &mat4) {
    os << "Mat4: [" << std::endl;
    for (int i = 0; i < 4; ++i) {
        os << "[";
        for (int j = 0; j < 4; ++j) {
            os << mat4.data[i][j];
            if (j != 3) os << " ";
        }
        os << "]";
        if (i != 3) os << std::endl;
        else os << "]";
    }
    return os;
}

/**
 *  class Transformation
 */
Mat4 Transformation::scale(float sx, float sy, float sz) {
    Mat4 mat4;
    mat4.setZero_();
    mat4.data[0][0] = sx;
    mat4.data[1][1] = sy;
    mat4.data[2][2] = sz;
    mat4.data[3][3] = 1.0f;
    return mat4;
}

Mat4 Transformation::transform(float tx, float ty, float tz) {
    Mat4 mat4;
    mat4.setIdentity_();
    mat4.data[0][3] = tx;
    mat4.data[1][3] = ty;
    mat4.data[2][3] = tz;
    return mat4;
}

Mat4 Transformation::rotateX(float degree) {
    Mat4 mat4;
    auto theta = (float) (degree * M_PI / 180);
    mat4.setIdentity_();
    mat4.data[1][1] = mat4.data[2][2] = cosf(theta);
    mat4.data[2][1] = sinf(theta);
    mat4.data[1][2] = -mat4.data[2][1];
    return mat4;
}

Mat4 Transformation::rotateY(float degree) {
    Mat4 mat4;
    auto theta = (float) (degree * M_PI / 180);
    mat4.setIdentity_();
    mat4.data[0][0] = mat4.data[2][2] = cosf(theta);
    mat4.data[0][2] = sinf(theta);
    mat4.data[2][0] = -mat4.data[0][2];
    return mat4;
}

Mat4 Transformation::rotateZ(float degree) {
    Mat4 mat4;
    auto theta = (float) (degree * M_PI / 180);
    mat4.setIdentity_();
    mat4.data[0][0] = mat4.data[1][1] = cosf(theta);
    mat4.data[1][0] = sinf(theta);
    mat4.data[0][1] = -mat4.data[1][0];
    return mat4;
}

/**
 *  class Viewing
 */
void Viewing::orthoProject(Mat4 &mat4, float l, float r, float b, float t, float f, float n) {
    mat4.setIdentity_();
    mat4.data[0][0] = 2 / (r - l);
    mat4.data[1][1] = 2 / (t - b);
    mat4.data[2][2] = 2 / (n - f);
    mat4.data[0][3] = -(r + l) / (r - l);
    mat4.data[1][3] = -(t + b) / (t - b);
    mat4.data[2][3] = -(n + f) / (n - f);
}

void Viewing::viewport(Mat4 &mat4, int width, int height) {
    mat4.setIdentity_();
    mat4.data[0][0] = (float) width * 1.0f / 2;
    mat4.data[1][1] = (float) height * 1.0f / 2;
    mat4.data[0][3] = (float) (width - 1) * 1.0f / 2;
    mat4.data[1][3] = (float) (height - 1) * 1.0f / 2;
}

void Viewing::perspToOrtho(Mat4 &mat4, float n, float f) {
    mat4.setZero_();
    mat4.data[0][0] = mat4.data[1][1] = n;
    mat4.data[2][2] = n + f;
    mat4.data[2][3] = -f * n;
    mat4.data[3][2] = 1.0f;
}

/**
 *  class LineSeg
 */
LineSeg::LineSeg(const Vec4 &from, const Vec4 &to) : from(from), to(to) {}

void LineSeg::transform(const Mat4& mat4) {
    from = mat4 * from;
    to = mat4 * to;
}

void LineSeg::render(Byte *pFrameBuffer, int width, int height) const {
    double k = (to.y - from.y) / (to.x - from.x);
    if (abs(k) <= 1) {
        double b = from.y - from.x * k;
        int _min = (int)min(from.x, to.x);
        int _max = (int)max(from.x, to.x);
        int x = _min;
        double y = k * x + b;
        int i = width*4*(int) y + x*4;
        pFrameBuffer[i  ] = 0;
        pFrameBuffer[i+1] = 0;
        pFrameBuffer[i+2] = 0;
        pFrameBuffer[i+3] = 0;
        for (x++; x <= _max; ++x) {
            y += k;
            i = width*4*(int) y + x*4;
            pFrameBuffer[i  ] = 0;
            pFrameBuffer[i+1] = 0;
            pFrameBuffer[i+2] = 0;
            pFrameBuffer[i+3] = 0;
        }
    } else {
        k = 1 / k;
        double b = from.x - from.y * k;
        int _min = (int)min(from.y, to.y);
        int _max = (int)max(from.y, to.y);
        int y = _min;
        double x = k * y + b;
        int i = width*4*y + (int)x*4;
        pFrameBuffer[i  ] = 0;
        pFrameBuffer[i+1] = 0;
        pFrameBuffer[i+2] = 0;
        pFrameBuffer[i+3] = 0;
        for (y++; y <= _max; ++y) {
            x += k;
            i = width*4*y + (int)x*4;
            pFrameBuffer[i  ] = 0;
            pFrameBuffer[i+1] = 0;
            pFrameBuffer[i+2] = 0;
            pFrameBuffer[i+3] = 0;
        }
    }
}

void LineSeg::divideW_() {
    from.divideW_();
    to.divideW_();
}

/**
 *  class WireFrame
 */
void WireFrame::transform(const Mat4 &mat4) const {
    for (int i = 0; i < size; ++i) {
        lines[i].transform(mat4);
    }
}

void WireFrame::render(Byte *pFrameBuffer, int width, int height) const {
    for (int i = 0; i < size; ++i) {
        lines[i].render(pFrameBuffer, width, height);
    }
}

void WireFrame::show() const {
    for (int i = 0; i < size; ++i) {
        char text[128] = {0};
        sprintf(text, "\n(%f,%f,%f)->(%f,%f,%f)",
                lines[i].from.x, lines[i].from.y, lines[i].from.z,
                lines[i].to.x, lines[i].to.y, lines[i].to.z);
        WriteConsoleA(hConsole, text, 128, nullptr, nullptr);
    }
}

void WireFrame::divideW_() const {
    for (int i = 0; i < size; ++i) lines[i].divideW_();
}

/**
 *  class CubeFrame
 */

CubeFrame::CubeFrame(const Vec4 &center, float width) {
    size = 12;
    lines = (LineSeg*) malloc(sizeof(LineSeg)*size);
    float half = width / 2;
    lines[0] = LineSeg(center.add(Vec4(-half,-half,-half,1)),
                      center.add(Vec4(half, -half, -half, 1)));
    lines[1] = LineSeg(center.add(Vec4(half,-half,-half,1)),
                      center.add(Vec4(half, -half, half, 1)));
    lines[2] = LineSeg(center.add(Vec4(half,-half,half,1)),
                      center.add(Vec4(-half, -half, half, 1)));
    lines[3] = LineSeg(center.add(Vec4(-half,-half,half,1)),
                      center.add(Vec4(-half, -half, -half, 1)));
    lines[4] = LineSeg(center.add(Vec4(-half,half,-half,1)),
                      center.add(Vec4(half, half, -half, 1)));
    lines[5] = LineSeg(center.add(Vec4(half,half,-half,1)),
                      center.add(Vec4(half, half, half, 1)));
    lines[6] = LineSeg(center.add(Vec4(half,half,half,1)),
                      center.add(Vec4(-half, half, half, 1)));
    lines[7] = LineSeg(center.add(Vec4(-half,half,half,1)),
                      center.add(Vec4(-half, half, -half, 1)));
    lines[8] = LineSeg(center.add(Vec4(-half,-half,-half,1)),
                      center.add(Vec4(-half, half, -half, 1)));
    lines[9] = LineSeg(center.add(Vec4(half,-half,-half,1)),
                      center.add(Vec4(half, half, -half, 1)));
    lines[10] = LineSeg(center.add(Vec4(half,-half,half,1)),
                      center.add(Vec4(half, half, half, 1)));
    lines[11] = LineSeg(center.add(Vec4(-half,-half,half,1)),
                      center.add(Vec4(-half, half, half, 1)));
}

CubeFrame::~CubeFrame() {
    free(lines);
    lines = nullptr;
    size = 0;
}

