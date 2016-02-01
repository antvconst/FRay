#ifndef CAMERA_H
#define CAMERA_H

#include "math/math.h"

class Scene; // forward declaration to avoid mutual inclusion (camera needs only a pointer to the scene)

class Camera
{
private:
    Vec3 position;
    Vec3 lookAt;
    Vec3 up;
    double fovy;
    Scene* scene;

public:
    Camera(Scene* scene, const Vec3& position, const Vec3& lookAt, const Vec3& up, double fovy);
};

#endif // CAMERA_H
