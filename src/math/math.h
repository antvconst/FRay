#ifndef MATH_H
#define MATH_H

#include <cmath>

#include "vector.h"
#include "matrix.h"

typedef Vector<2> Vec2;
typedef Vector<3> Vec3;
typedef Vector<4> Vec4;
typedef Matrix<2> Mat2;
typedef Matrix<3> Mat3;
typedef Matrix<4> Mat4;

typedef Vector<2> Sample;
typedef Vector<3> Color;

Vec3 as_vec3(const Vec4& v);
Vec4 as_vec4(const Vec3& v);
Vec4 as_point(const Vec3& v);
Mat3 submatrix(const Mat4& m);
Vec3 cross(const Vec3& u, const Vec3& v);
double dot(const Vec3& u, const Vec3& v);
Mat3 cprod_matrix(const Vec3& v);
Mat3 rotation_matrix(const Vec3& v, double theta);
Vec3 barycentric_coordinates(const Vec4& A, const Vec4& B, const Vec4& C, const Vec4& P);

#endif // MATH_H

