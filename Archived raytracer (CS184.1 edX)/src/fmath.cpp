#include "fmath.h"

/*
 * MATRIX3 BEGIN
*/
Matrix3::Matrix3() {
    for (int n=0; n<N; n++)
        for (int m=0; m<N; m++)
            this->operator()(n, m) = 0;
}


Matrix3::Matrix3(const Matrix3 &another) {
    for (int n=0; n<N; n++)
        for (int m=0; m<N; m++)
            this->operator()(n, m) = another(n, m);
}

Matrix3::Matrix3(Matrix4 &mat4) {
    *this = mat4.submatrix();
}

Matrix3 Matrix3::identity() {
    Matrix3 mat;
    for (int i=0; i<N; i++)
        mat(i, i) = 1;

    return mat;
}

const float &Matrix3::operator()(int i, int j) const {
    if ((i <= N) && (j <= N))
        return this->data[i][j];
    else
        throw std::exception();
}

Matrix3 Matrix3::operator+(const Matrix3& another) const {
    Matrix3 mat;

    for (int n=0; n<N; n++)
        for (int m=0; m<N; m++)
            mat(n, m) = this->operator ()(n, m) + another(n, m);

    return mat;
}

Matrix3 Matrix3::operator-(const Matrix3& another) const {
    Matrix3 mat;

    for (int n=0; n<N; n++)
        for (int m=0; m<N; m++)
            mat(n, m) = this->operator ()(n, m) - another(n, m);

    return mat;
}

Matrix3 Matrix3::operator*(const Matrix3& another) const {
    Matrix3 mat;
    float current_product;

    for (int n=0; n<N; n++)
        for (int m=0; m<N; m++)
        {
            current_product = 0;
            for (int k=0; k<N; k++)
                current_product += this->operator ()(n, k) * another(k, m);
            mat(n, m) = current_product;
        }

    return mat;
}

Matrix3 Matrix3::operator*(const float scalar) const {
    Matrix3 mat;

    for (int n=0; n<N; n++)
        for (int m=0; m<N; m++)
            mat(n, m) = this->operator ()(n, m) * scalar;

    return mat;
}

Vector3 Matrix3::operator*(const Vector3& vec) const {
    Vector3 product;

    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            product.el(i) += vec.el(j) * this->operator ()(i, j);

    return product;
}

Matrix3 Matrix3::transposed() const {
    Matrix3 mat;

    for (int n=0; n<N; n++)
        for (int m=0; m<N; m++)
            mat(n, m) = this->operator ()(m, n);

    return mat;
}

void Matrix3::transpose() {
    *this = this->transposed();
}

Matrix3 Matrix3::inverse() {
    if (hasInverse)
        return *precomputedInverse;

    Matrix3 m(*this);

    Matrix3 mat;
    for (unsigned column = 0; column < N; ++column) {
        // Swap row in case our pivot point is not working
        if (m(column, column) == 0) {
            unsigned big = column;
            for (unsigned row = 0; row < N; ++row)
                if (fabs(m(row, column)) > fabs(m(big, column))) big = row;
            // Print this is a singular matrix, return identity ?
            if (big == column) {}//std::cerr << "Singular matrix" << std::endl;
            // Swap rows
            else for (unsigned j = 0; j < N; ++j) {
                std::swap(m(column, j), m(big, j));
                std::swap(mat(column, j), mat(big, j));
            }
        }
        // Set each row in the column to 0
        for (unsigned row = 0; row < N; ++row) {
            if (row != column) {
                float coeff = m(row, column) / m(column, column);
                if (coeff != 0) {
                    for (unsigned j = 0; j < N; ++j) {
                        m(row, j) -= coeff * m(column, j);
                        mat(row, j) -= coeff * mat(column, j);
                    }
                    // Set the element to 0 for safety
                    m(row, column) = 0;
                }
            }
        }
    }
    // Set each element of the diagonal to 1
    for (unsigned row = 0; row < N; ++row) {
        for (unsigned column = 0; column < N; ++column) {
            mat(row, column) /= m(row, row);
        }
    }
    precomputedInverse = new Matrix3(mat);
    hasInverse = true;
    return *precomputedInverse;
}

void Matrix3::invert() {
    *this = this->inverse();
}

void Matrix3::print() {
    for (int n=0; n<N; n++)
    {
        for (int m=0; m<N; m++)
            std::cout << this->operator ()(n, m) << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

float& Matrix3::operator()(int i, int j) {
    if ((i <= N) && (j <= N))
        return this->data[i][j];
    else
        throw std::exception();
}
/*
 * MATRIX3 END
*/



/*
 * MATRIX4 BEGIN
*/
Matrix4::Matrix4() {
    for (int n=0; n<N; n++)
        for (int m=0; m<N; m++)
            this->operator()(n, m) = 0;
}


Matrix4::Matrix4(const Matrix4 &another) {
    for (int n=0; n<N; n++)
        for (int m=0; m<N; m++)
            this->operator()(n, m) = another(n, m);
}

Matrix4::Matrix4(const Matrix3 &mat3) {
    *this = Matrix4::identity();
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            this->operator ()(i, j) = mat3(i, j);
}

Matrix4 Matrix4::identity() {
    Matrix4 mat;
    for (int i=0; i<N; i++)
        mat(i, i) = 1;

    return mat;
}

const float &Matrix4::operator()(int i, int j) const {
    if ((i <= N) && (j <= N))
        return this->data[i][j];
    else
        throw std::exception();
}

Matrix4 Matrix4::operator+(const Matrix4 &another) const {
    Matrix4 mat;

    for (int n=0; n<N; n++)
        for (int m=0; m<N; m++)
            mat(n, m) = this->operator ()(n, m) + another(n, m);

    return mat;
}

Matrix4 Matrix4::operator-(const Matrix4 &another) const {
    Matrix4 mat;

    for (int n=0; n<N; n++)
        for (int m=0; m<N; m++)
            mat(n, m) = this->operator ()(n, m) - another(n, m);

    return mat;
}

Matrix4 Matrix4::operator*(const Matrix4 &another) const {
    Matrix4 mat;
    float current_product;

    for (int n=0; n<N; n++)
        for (int m=0; m<N; m++)
        {
            current_product = 0;
            for (int k=0; k<N; k++)
                current_product += this->operator ()(n, k) * another(k, m);
            mat(n, m) = current_product;
        }

    return mat;
}

Matrix4 Matrix4::operator*(const float scalar) const {
    Matrix4 mat;

    for (int n=0; n<N; n++)
        for (int m=0; m<N; m++)
            mat(n, m) = this->operator ()(n, m) * scalar;

    return mat;
}

Vector4 Matrix4::operator*(const Vector4& vec) const {
    Vector4 product;

    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            product.el(i) += vec.el(j) * this->operator ()(i, j);

    return product;
}

Matrix4 Matrix4::transposed() const {
    Matrix4 mat;

    for (int n=0; n<N; n++)
        for (int m=0; m<N; m++)
            mat(n, m) = this->operator ()(m, n);

    return mat;
}

void Matrix4::transpose() {
    *this = this->transposed();
}

Matrix4 Matrix4::inverse() {
    Matrix4 m(*this);

    Matrix4 mat = Matrix4::identity();
    for (unsigned column = 0; column < N; ++column) {
        // Swap row in case our pivot point is not working
        if (m(column, column) == 0) {
            unsigned big = column;
            for (unsigned row = 0; row < N; ++row)
                if (fabs(m(row, column)) > fabs(m(big, column))) big = row;
            // Print this is a singular matrix, return identity ?
            if (big == column) fprintf(stderr, "Singular matrix\n");
            // Swap rows
            else for (unsigned j = 0; j < N; ++j) {
                std::swap(m(column, j), m(big, j));
                std::swap(mat(column, j), mat(big, j));
            }
        }
        // Set each row in the column to 0
        for (unsigned row = 0; row < N; ++row) {
            if (row != column) {
                float coeff = m(row, column) / m(column, column);
                if (coeff != 0) {
                    for (unsigned j = 0; j < N; ++j) {
                        m(row, j) -= coeff * m(column, j);
                        mat(row, j) -= coeff * mat(column, j);
                    }
                    // Set the element to 0 for safety
                    m(row, column)= 0;
                }
            }
        }
    }
    // Set each element of the diagonal to 1
    for (unsigned row = 0; row < N; ++row) {
        for (unsigned column = 0; column < N; ++column) {
            mat(row, column) /= m(row, row);
        }
    }
    return mat;
}

void Matrix4::invert() {
    *this = this->inverse();
}

Matrix3 Matrix4::submatrix() const {
    Matrix3 submat;
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            submat(i, j) = this->operator ()(i, j);

    return submat;
}

void Matrix4::setSubmatrix(Matrix3 &mat3) {
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            this->operator ()(i, j) = mat3(i, j);
}

void Matrix4::print() const {
    for (int n=0; n<N; n++)
    {
        for (int m=0; m<N; m++)
            std::cout << this->operator ()(n, m) << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

float &Matrix4::operator()(int i, int j) {
    if ((i <= N) && (j <= N))
        return this->data[i][j];
    else
        throw std::exception();
}
/*
 * MATRIX3 BEGIN
*/



/*
 * VECTOR3 BEGIN
*/
Vector3::Vector3() {
    for (int i=0; i<N; i++)
        this->data[i] = 0;
}

Vector3::Vector3(float x, float y, float z) {
    this->x() = x;
    this->y() = y;
    this->z() = z;
}

float& Vector3::x() {
    return this->el(0);
}

const float& Vector3::x() const {
    return this->el(0);
}

float& Vector3::y() {
    return this->el(1);
}

const float& Vector3::y() const{
    return this->el(1);
}

float& Vector3::z() {
    return this->el(2);
}

const float& Vector3::z() const {
    return this->el(2);
}

float& Vector3::el(int idx) {
    return this->data[idx];
}

const float& Vector3::el(int idx) const {
    return this->data[idx];
}

Vector3 Vector3::operator+(const Vector3& another) const {
    Vector3 vec;
    for (int i=0; i<N; i++)
        vec.el(i) = this->el(i) + another.el(i);
    return vec;
}

float Vector3::dot(const Vector3& another) const {
    return this->x() * another.x() +
           this->y() * another.y() +
           this->z() * another.z();
}

Vector3 Vector3::cross(const Vector3& another) const {
    return Vector3(this->y() * another.z() - this->z() * another.y(),
                   this->z() * another.x() - this->x() * another.z(),
                   this->x() * another.y() - this->y() * another.x());
}

float Vector3::magnitude() const {
    return sqrt(this->x() * this->x() +
                this->y() * this->y() +
                this->z() * this->z());
}

Vector3 Vector3::normalized() const {
    return *this / this->magnitude();
}

void Vector3::normalize() {
    *this = *this / this->magnitude();
}

Vector3 Vector3::operator*(const float scalar) const {
    Vector3 vec;
    for (int i=0; i<N; i++)
        vec.el(i) = this->el(i) * scalar;
    return vec;
}

Vector3 Vector3::operator*(const Vector3& another) const
{
    Vector3 vec;
    for (int i=0; i<N; i++)
        vec.el(i) = this->el(i) * another.el(i);
    return vec;
}

Vector3 Vector3::operator-() const {
    return Vector3(-this->x(), -this->y(), -this->z());
}

Vector3 Vector3::operator-(const Vector3& another) const {
    Vector3 vec;
    for (int i=0; i<N; i++)
        vec.el(i) = this->el(i) - another.el(i);
    return vec;
}

Vector3 Vector3::operator/(const float scalar) const {
    Vector3 vec;
    for (int i=0; i<N; i++)
        vec.el(i) = this->el(i) / scalar;
    return vec;
}

void Vector3::print() const {
    for (int n=0; n<N; n++)
        cout << this->el(n) << " ";
    std::cout << std::endl;
}
/*
 * VECTOR3 END
*/



/*
 * VECTOR4 BEGIN
*/
Vector4::Vector4() {
    for (int i=0; i<N; i++)
        this->data[i] = 0;
}

Vector4::Vector4(float x, float y, float z, float w) {
    this->x() = x;
    this->y() = y;
    this->z() = z;
    this->w() = w;
}

Vector4::Vector4(const Vector3& vec3, float w=0) {
    this->x() = vec3.x();
    this->y() = vec3.y();
    this->z() = vec3.z();
    this->w() = w;
}

float& Vector4::x() {
    return this->el(0);
}

const float& Vector4::x() const {
    return this->el(0);
}

float& Vector4::y() {
    return this->el(1);
}

const float& Vector4::y() const {
    return this->el(1);
}

float& Vector4::z() {
    return this->el(2);
}

const float& Vector4::z() const {
    return this->el(2);
}

float& Vector4::w() {
    return this->el(3);
}

const float& Vector4::w() const {
    return this->el(3);
}

float& Vector4::el(int idx) {
    return this->data[idx];
}

const float& Vector4::el(int idx) const {
    return this->data[idx];
}

Vector3 Vector4::xyz() const {
    return Vector3(this->x(),
                   this->y(),
                   this->z());
}

Vector4 Vector4::operator+(const Vector4& another) const {
    Vector4 vec;
    for (int i=0; i<N-1; i++)
        vec.el(i) = this->el(i) + another.el(i);
    return vec;
}

float Vector4::dot(const Vector4& another) const {
    return this->x() * another.x() +
           this->y() * another.y() +
           this->z() * another.z();
}

Vector4 Vector4::cross(const Vector4& another) const {
    return Vector4(this->y() * another.z() - this->z() * another.y(),
                   this->z() * another.x() - this->x() * another.z(),
                   this->x() * another.y() - this->y() * another.x(),
                   this->w());
}

float Vector4::magnitude() const {
    return sqrt(this->x() * this->x() +
                this->y() * this->y() +
                this->z() * this->z());
}

Vector4 Vector4::normalized() const {
    return *this / this->magnitude();
}

void Vector4::normalize() {
    *this = *this / this->magnitude();
}

Vector4 Vector4::dehomogenized() const {
    Vector4 vec;
    for (int i=0; i<N; i++)
        vec.el(i) = this->el(i) / this->w();
    return vec;
}

void Vector4::dehomogenize() {
    for (int i=0; i<N; i++)
        this->el(i) /= this->w();
}

Vector4 Vector4::operator-() const {
    return Vector4(-this->x(), -this->y(), -this->z(), this->w());
}

Vector4 Vector4::operator-(const Vector4& another) const {
    Vector4 vec;
    for (int i=0; i<N-1; i++)
        vec.el(i) = this->el(i) - another.el(i);
    return vec;
}

Vector4 Vector4::operator*(const float scalar) const {
    Vector4 vec;
    for (int i=0; i<N-1; i++)
        vec.el(i) = this->el(i) * scalar;
    return vec;
}

Vector4 Vector4::operator/(const float scalar) const {
    Vector4 vec;
    for (int i=0; i<N-1; i++)
        vec.el(i) = this->el(i) / scalar;
    return vec;
}

void Vector4::print() {
    for (int n=0; n<N; n++)
        cout << this->el(n) << " ";
    std::cout << std::endl;
}
/*
 * VECTOR4 END
*/



Matrix4 rotation(float angle, Vector3& axis) {
    angle *= PI/180;

    Matrix3 dualMatrix;
    dualMatrix(0, 0) = 0;
    dualMatrix(0, 1) = -axis.z();
    dualMatrix(0, 2) = axis.y();
    dualMatrix(1, 0) = axis.z();
    dualMatrix(1, 1) = 0.0;
    dualMatrix(1, 2) = -axis.x();
    dualMatrix(2, 0) = -axis.y();
    dualMatrix(2, 1) = axis.x();
    dualMatrix(2, 2) = 0;

    Matrix3 wtfMatrix;
    wtfMatrix(0, 0) = axis.x() * axis.x();
    wtfMatrix(0, 1) = axis.x() * axis.y();
    wtfMatrix(0, 2) = axis.x() * axis.z();
    wtfMatrix(1, 0) = axis.x() * axis.y();
    wtfMatrix(1, 1) = axis.y() * axis.y();
    wtfMatrix(1, 2) = axis.y() * axis.z();
    wtfMatrix(2, 0) = axis.x() * axis.z();
    wtfMatrix(2, 1) = axis.y() * axis.z();
    wtfMatrix(2, 2) = axis.z() * axis.z();


    Matrix3 rotation = Matrix3::identity();
    rotation = (rotation * cos(angle)) +
            (wtfMatrix * (1-cos(angle))) +
            (dualMatrix * sin(angle));

    Matrix4 ret = Matrix4::identity();
    ret.setSubmatrix(rotation);

    return ret;
}


Matrix4 translation(float x, float y, float z) {
    Matrix4 translation = Matrix4::identity();

    translation(0, 3) = x;
    translation(1, 3) = y;
    translation(2, 3) = z;

    return translation;
}


Matrix4 scale(float x, float y, float z) {
    Matrix4 scale = Matrix4::identity();

    scale(0, 0) = x;
    scale(1, 1) = y;
    scale(2, 2) = z;

    return scale;
}


Vector3 computeReflectedDirection(Vector3& eyeDirection, Vector3& normal)
{
    return eyeDirection - (normal * 2 * eyeDirection.dot(normal));
}
