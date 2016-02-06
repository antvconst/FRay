#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>
#include "math/math.h"
#include "rendering/ray.h"

class Camera
{
private:
    Vec3 position, u, v, w; // (u, v, w) is the camera coordinate frame
    int height, width, hh, hw; // image dimensions
    double alpha, beta;

public:
    Camera();
    Camera(const Vec3& position, const Vec3& screen_center, const Vec3& up, double fovy, int height, int width);
    Ray generate_ray(int i, int j);
};

#endif // CAMERA_H
