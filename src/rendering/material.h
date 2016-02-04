#ifndef MATERIAL_H
#define MATERIAL_H

#include "math/math.h"

class Raytracer;

class Material
{
public:
    Material();

    Vec3 shade(Raytracer* rtracer, const Vec4& p, const Vec3& n);
};

#endif // MATERIAL_H
