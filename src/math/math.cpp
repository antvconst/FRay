#include "math/math.h"

Vec3 as_vec3(const Vec4& v) {
    return Vec3(v.el(0), v.el(1), v.el(2));
}

Vec4 as_vec4(const Vec3& v) {
    return Vec4(v.el(0), v.el(1), v.el(2), 0.0);
}


Vec4 as_point(const Vec3& v) {
    return Vec4(v.el(0), v.el(1), v.el(2), 1.0);
}



Mat3 submatrix(const Mat4& m) {
    Mat3 r;
    for (int i=0; i<3; ++i)
        for (int j=0; j<3; ++j)
            r.mut_el(i, j) = m.el(i, j);

    return r;
}


Vec3 cross(const Vec3& u, const Vec3& v) {
    return Vec3(u.el(1)*v.el(2) - v.el(1)*u.el(2),
                v.el(0)*u.el(2) - v.el(2)*u.el(0),
                u.el(0)*v.el(1) - v.el(0)*u.el(1));
}

double dot(const Vec3& u, const Vec3& v) {
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


Vec3 barycentric_coordinates(const Vec4& A, const Vec4& B, const Vec4& C, const Vec4& P) {
    Mat2 T(A.el(0)-C.el(0), B.el(0)-C.el(0),
           A.el(1)-C.el(1), B.el(1)-C.el(1));

    T.print();

    Vec2 V(P.el(0)-C.el(0),
           P.el(1)-C.el(1));

    Vec2 R = T.inverse() * V;

    double alpha = R.el(0);
    double beta = R.el(1);
    double gamma = 1-alpha-beta;

    return Vec3(alpha, beta, gamma);
}
