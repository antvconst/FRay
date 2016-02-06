#ifndef MATERIAL_H
#define MATERIAL_H

#include "math/math.h"

class Raytracer;

class Material
{
public:
    Color reflectance;

    Material() {}

    // ~light_color~ must be already multiplied by falloff factor!
    virtual Vec3 shade(const Vec3& v, const Vec3& n, const Vec3& l, Color light_color);
};

#endif // MATERIAL_H
