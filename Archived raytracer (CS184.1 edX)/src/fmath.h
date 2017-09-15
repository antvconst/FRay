#ifndef FMATH_H
#define FMATH_H

#include <cmath>
#include <iostream>
using namespace std;


// FORWARD DECLARATIONS //
class Matrix3;
class Matrix4;
class Vector3;
class Vector4;
const float PI = 3.14159265;

// MATRIX3 BEGIN //

class Matrix3
{
private:
    static const int N = 3;
    float data[N][N];

public:
    Matrix3();
    Matrix3(const Matrix3& another);
    Matrix3(Matrix4 &mat4);
    static Matrix3 identity();

    float& operator() (int i, int j);
    const float& operator() (int i, int j) const;

    Matrix3 operator+ (const Matrix3& another) const;
    Matrix3 operator- (const Matrix3& another) const;
    Matrix3 operator* (float scalar) const;
    Matrix3 operator* (const Matrix3& another) const;
    Vector3 operator* (const Vector3& vec) const;

    Matrix3 transposed() const;
    void transpose();

    Matrix3 inverse();
    void invert();

    bool hasInverse = false;
    Matrix3* precomputedInverse;

    void print();
};

// MATRIX3 END //

// MATRIX4 BEGIN //
class Matrix4
{
private:
    static const int N = 4;
    float data[N][N];

public:
    Matrix4();
    Matrix4(const Matrix4 &another);
    Matrix4(const Matrix3 &mat3);
    static Matrix4 identity();

    float& operator() (int i, int j);
    const float& operator() (int i, int j) const;

    Matrix4 operator+ (const Matrix4& another) const;
    Matrix4 operator- (const Matrix4& another) const;
    Matrix4 operator* (const float scalar) const;
    Matrix4 operator* (const Matrix4& another) const;
    Vector4 operator*(const Vector4& vec) const;

    Matrix4 transposed() const;
    void transpose();

    Matrix4 inverse();
    void invert();

    Matrix3 submatrix() const;
    void setSubmatrix(Matrix3& mat3);

    bool hasInverse = false;
    Matrix4* precomputedInverse;

    void print() const;
};

// MATRIX4 END //

// VECTOR3 BEGIN //

class Vector3
{
private:
    static const int N = 3;
    float data[N];

public:
    Vector3();
    Vector3(float x, float y, float z);

    float& x();
    const float& x() const;
    float& y();
    const float& y() const;
    float& z();
    const float& z() const;
    float& el(int idx);
    const float& el(int idx) const;

    Vector3 operator+ (const Vector3& another) const;

    float dot(const Vector3& another) const;
    Vector3 cross(const Vector3& another) const;
    float magnitude() const;
    Vector3 normalized() const;
    void normalize();
    Vector3 dehomogenized() const;
    void dehomogenize();

    Vector3 operator-() const;
    Vector3 operator- (const Vector3& another) const;
    Vector3 operator* (const float scalar) const;
    Vector3 operator* (const Vector3& another) const;
    Vector3 operator/ (const float scalar) const;

    void print() const;
};

// VECTOR3 END //

// VECTOR4 BEGIN //
class Vector4
{
private:
    static const int N = 4;
    float data[N];

public:
    Vector4();
    Vector4(float x, float y, float z, float w);
    Vector4(const Vector3& vec3, float w);

    float& x();
    const float& x() const;
    float& y();
    const float& y() const;
    float& z();
    const float& z() const;
    float& w();
    const float& w() const;
    float& el(int idx);
    const float& el(int idx) const;
    Vector3 xyz() const;

    Vector4 operator+ (const Vector4 &another) const;

    float dot(const Vector4& another) const;
    Vector4 cross(const Vector4& another) const;
    float magnitude() const;
    Vector4 normalized() const;
    void normalize();
    Vector4 dehomogenized() const;
    void dehomogenize();

    Vector4 operator-() const;
    Vector4 operator- (const Vector4& another) const;
    Vector4 operator* (const float scalar) const;
    Vector4 operator/ (const float scalar) const;

    void print();
};

Matrix4 rotation(float angle, Vector3& axis);
Matrix4 translation(float x, float y, float z);
Matrix4 scale(float x, float y, float z);
Vector3 computeReflectedDirection(Vector3& eyeDirection, Vector3& normal);

// VECTOR4 END //

#endif
