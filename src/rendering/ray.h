#ifndef RAY_H
#define RAY_H

#include "math/math.h"

class Ray
{    
public:
    Vec4 origin;
    Vec3 direction;

    Ray() {}
    Ray(const Vec4& origin, const Vec3& direction) : origin(origin), direction(direction) {}
};

#endif // RAY_H
