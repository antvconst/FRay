#include "sphere.h"

Sphere::Sphere(const Vec4& center, double radius) :
    center(center), radius(radius) {}

bool Sphere::intersect(const Ray& r, LocalGeometry& lgeo) {
    Mat4 TInv = this->transform.inverse();
    Vec3 d = as_vec3(TInv*as_vec4(r.direction));
    Vec3 P0 = as_vec3(TInv*r.origin);
    Vec3 C = as_vec3(this->center);

    Vec3 P = P0 - C;
    double a = dot(d, d);
    double b = dot(P, d);
    double c = dot(P, P) - radius*radius;

    double D = b*b - a*c;

    if (D < 0.0)
        return false;

    else {
        double t;

        if (D == 0.0) {
            t = -b/2*a;
            if (t < 0.0)
                return false;
        }
        else {
            double sqrt_D = sqrt(D);
            double rec_2a = 1/(2*a);
            double t1 = (-b+sqrt_D)*rec_2a;
            double t2 = (-b-sqrt_D)*rec_2a;

            if (t1 < 0.0 && t2 < 0.0)
                return false;
            else if (t1 > 0.0 && t2 > 0.0)
                t = std::min(t1, t2);
            else
                t = std::max(t1, t2);
        }

        Vec4 point = as_point(P0 + d*t);
        Vec3 normal = as_vec3(point-center).normalize();

        lgeo.geo = this;
        lgeo.normal = normal;
        lgeo.point = point;
        return true;
    }
}


