#ifndef SPHERE_H
#define SPHERE_H

#include "geometry.h"

class Sphere : Geometry
{
public:
    Vec4 center;
    double radius;

    Sphere(const Vec4& center, double radius);
    bool intersect(const Ray &r, LocalGeometry &lgeo);
};

#endif // SPHERE_H
