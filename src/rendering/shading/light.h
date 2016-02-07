#ifndef LIGHT_H
#define LIGHT_H

#include "math/math.h"

class Light
{
public:
    Vec3 position;
    Color color;

    Light(const Vec3& position, const Color& color);
    virtual double intensity(double distance) = 0;
};

class PointLight : Light
{
public:
    double attenuation_const;
    double attenuation_linear;
    double attenuation_quadratic;

    PointLight(const Vec3& position, const Color& color, const Vec3& attenuation);
    double intensity(double distance);
};

class DirectionalLight : Light
{
public:
    DirectionalLight(const Vec3& position, const Color& color);
    double intensity(double distance);
};

#endif // LIGHT_H
