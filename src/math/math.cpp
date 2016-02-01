#include "math/math.h"

Vec3 toVec3(const Vec4& v) {
    return Vec3(v.el(0), v.el(1), v.el(2));
}

Vec3 cross(const Vec3& u, const Vec3& v) {
    return Vec3(u.el(1)*v.el(2) - v.el(1)*u.el(2),
                v.el(0)*u.el(2) - v.el(2)*u.el(0),
                u.el(0)*v.el(1) - v.el(0)*u.el(1));
}

Vec3 dot(const Vec3& u, const Vec3& v) {
    return u.el(0)*v.el(0) + u.el(1)*v.el(1) + u.el(2)*v.el(2);
}

Mat3 cprod_matrix(const Vec3& v) {
    double x = v.el(0);
    double y = v.el(1);
    double z = v.el(2);

    return Mat3(0.0, -z, y,
                z, 0.0, -x,
                -y, x, 0.0);
}

Mat3 rotation_matrix(const Vec3& v, double theta) {
    Mat3 V = cprod_matrix(v);
    return Mat3::identity() + (V*V)*(1-cos(theta)) + V*sin(theta);
}
