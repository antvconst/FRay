#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "math/math.h"
#include "rendering/ray.h"
#include "rendering/shading/material.h"

class Geometry; // necessary to define Geometry* inside LocalGeometry

class LocalGeometry
{
public:
    Geometry* geo;
    Vec4 point;
    Vec3 normal;

    LocalGeometry(Geometry* geo, const Vec4& point, const Vec3& normal) :
        geo(geo), point(point), normal(normal) {}
};

class Geometry
{
public:
    Mat4 transform;
    Material* material;

    Geometry() {}
    virtual bool intersect(const Ray& r, LocalGeometry& lgeo) = 0;
};

#endif // GEOMETRY_H
