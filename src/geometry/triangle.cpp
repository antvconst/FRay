#include "triangle.h"

Triangle::Triangle(const Vec4& A, const Vec4& B, const Vec4& C) :
    A(A), B(B), C(C) {
    Vec4 AB = B-A;
    Vec4 AC = C-A;
    this->normal = cross(as_vec3(AB), as_vec3(AC)).normalize();
}

bool Triangle::intersect(const Ray& r, LocalGeometry& lgeo) {
    Mat4 TInv = this->transform.inverse();
    Vec3 dir = as_vec3(TInv*as_vec4(r.direction));
    Vec4 origin = TInv*r.origin;


    if (cross(dir, normal).is_zero())
        return false;

    double t = dot(as_vec3(origin-A), normal)/dot(dir, normal);

    if (t < 0.0)
        return false;
    else {
        Vec4 point = origin + (as_vec4(dir) * t);

        Vec3 bar_coords = barycentric_coordinates(A, B, C, point);

        double alpha = bar_coords.el(0);
        double beta = bar_coords.el(1);
        double gamma = bar_coords.el(2);

        if (alpha < 0.0 || beta < 0.0 || gamma < 0.0)
            return false;

        else {
            lgeo.normal = submatrix(transform).inverse().transpose() * normal;
            lgeo.point = transform * point;
            lgeo.geo = this;
            return true;
        }
    }
}

