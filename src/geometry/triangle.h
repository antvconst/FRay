#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "geometry.h"

class Triangle : Geometry
{
public:
    Vec4 A, B, C;
    Vec3 normal;

    Triangle(const Vec4& A, const Vec4& B, const Vec4& C);
    bool intersect(const Ray &r, LocalGeometry &lgeo);
};

#endif // TRIANGLE_H
