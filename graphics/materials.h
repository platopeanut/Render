#ifndef RENDER_MATERIALS_H
#define RENDER_MATERIALS_H

#include "utils.h"

class Material {
public:
    virtual Color evaluate(const Vec3& l, const Vec3& v, const Vec3& n) = 0;
};

class BasicMaterial: Material {
public:
    Color color;
    explicit BasicMaterial(const Color &color);
    Color evaluate(const Vec3 &l, const Vec3 &v, const Vec3 &n) override;
};


#endif //RENDER_MATERIALS_H
