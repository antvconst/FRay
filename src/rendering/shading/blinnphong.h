#ifndef BLINNPHONG_H
#define BLINNPHONG_H

#include <algorithm>

#include "material.h"
#include "light.h"
#include "math/math.h"

class BlinnPhong : public Material
{
public:
    Color diffuse;
    Color emissive;
    Color specular;
    Color reflectance;
    double shininess;

    BlinnPhong();
    Color shade(const Vec3& v, const Vec3& n, const Vec3& l, Color light_color);
};

#endif // BLINNPHONG_H
