#include "camera.h"

Camera::Camera() {}

Camera::Camera(const Vec3& position, const Vec3& screen_center, const Vec3& up, double fovy, int height, int width) :
    position(position), height(height), width(width), hh(height/2), hw(width/2) {

    this->w = (position-screen_center).normalize(); // conventionally looking down -Z
    this->u = cross(up, this->w).normalize(); // X
    this->v = cross(this->w, this->u); // Y

    double th_fovy = tan(0.5*fovy);
    double th_fovx = th_fovy * (width/height);

    this->alpha = th_fovx/hw; // pixel width
    this->beta = th_fovy/hh; // pixel height
}

Ray Camera::generate_ray(int i, int j) {
    Ray r;
    r.origin = position;
    r.direction = -w + u*((j-hw)*alpha) + v*((hh-i)*beta);
    return r;
}
