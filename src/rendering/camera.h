#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>
#include "math/math.h"
#include "rendering/ray.h"

class Scene; // forward declaration to avoid mutual inclusion (camera needs only a pointer to the scene)

class Camera
{
private:
    Vec3 position, u, v, w; // (u, v, w) is the camera coordinate frame
    double th_fovy, th_fovx; // tangents of half field of view x and y
    int height, width; // image dimensions
    double ratio; // width over height
    Scene* scene;

public:
    Camera();
    Camera(Scene* scene, const Vec3& position, const Vec3& screen_center, const Vec3& up, double fovy, int h, int w);
};

#endif // CAMERA_H
