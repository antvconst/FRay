#include "camera.h"

Camera::Camera() {}

Camera::Camera(Scene* scene, const Vec3& position, const Vec3& screen_center, const Vec3& up, double fovy, int h, int w) {
    this->scene = scene;
    this->position = position;

    this->w = (position-screen_center).normalize();
    this->u = cross(up, this->w).normalize();
    this->v = cross(this->w, this->u);

    this->height = h;
    this->width = w;
    this->ratio = w/h;

    this->th_fovy = tan(fovy/2);
    this->th_fovx = this->th_fovy * this->ratio;
}
