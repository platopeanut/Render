#include "materials.h"

/**
 *  class Basic Material
 */
BasicMaterial::BasicMaterial(const Color &color) : color(color) {}

Color BasicMaterial::evaluate(const Vec3 &l, const Vec3 &v, const Vec3 &n) {
    return this->color;
}
