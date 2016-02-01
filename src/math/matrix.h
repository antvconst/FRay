#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <stdexcept>
#include <cstdarg>
#include "vector.h"

template<int N>
class Matrix
{
private:
    double data[N][N];

public:
    Matrix() {}

    Matrix(double e, ...) {
        std::va_list args;
        va_start(args, e);
        double t = e;

        for (int i=0; i<N; ++i)
            for (int j=0; j<N; ++j) {
                mut_el(i, j) = t;
                t = va_arg(args, double);
            }
    }

    const double& el(int i, int j) const {
        return data[i][j];
    }

    double& mut_el(int i, int j) {
        return const_cast<double&>(el(i, j));
    }

    Matrix<N> operator+ (const Matrix<N>& m) const {
        Matrix<N> r;
        for (int i=0; i<N; ++i)
            for (int j=0; j<N; ++j) {
                r.mut_el(i,j) = this->el(i, j) + m.el(i, j);
            }

        return r;
    }

    Matrix<N> operator- (const Matrix<N>& m) const {
        Matrix<N> r;
        for (int i=0; i<N; ++i)
            for (int j=0; j<N; ++j) {
                r.mut_el(i,j) = this->el(i, j) - m.el(i, j);
            }

        return r;
    }

    Matrix<N> operator* (const Matrix<N>& m) const {
        Matrix<N> r;
        for (int i=0; i<N; ++i)
            for (int j=0; j<N; ++j) {
                double e = 0.0f;
                for (int k=0; k<N; ++k) {
                    e += this->el(i, k) * m.el(k, j);
                }
                r.mut_el(i, j) = e;
            }

        return r;
    }

    Matrix<N> operator* (double alpha) const {
        Matrix<N> r;
        for (int i=0; i<N; ++i)
            for (int j=0; j<N; ++j) {
                r.mut_el(i,j) = alpha * this->el(i, j);
            }

        return r;
    }

    Vector<N> operator* (Vector<N> v) const {
        Vector<N> r;
        for (int i=0; i<N; ++i) {
            double e = 0.0;
            for (int k=0; k<N; ++k)
                e += el(i, k) * v.el(k);
            r.mut_el(i) = e;
        }

        return r;
    }

    Matrix<N> operator/ (double alpha) const {
        return (*this)*(1/alpha);
    }

    Matrix<N> transpose() const {
        Matrix<N> r;
        for (int i=0; i<N; ++i)
            for (int j=0; j<N; ++j) {
                r.mut_el(i, j) = this->el(j, i);
            }

        return r;
    }

    Matrix<N> inverse() const {
        /* Using standard Gaussian elimination */

        Matrix<N> m = *this;
        Matrix<N> inv = Matrix<N>::identity();

        // reduce the matrix to upper-triangular
        for (int i=0; i<N; ++i) {
            // try to find non-zero element if the pivot is zero
            if (m.el(i, i) == 0.0f) {
                for (int k=i; k<N; ++k) {
                    if (m.el(k, i) != 0) {
                        m.swap_rows(i, k);
                        inv.swap_rows(i, k);
                        break;
                    }
                    if (k == N-1) // in case no non-zero element found (it means the matrix is singular)
                        throw std::runtime_error("Singular matrix");
                }
            }

            double s = -1/m.el(i, i);
            for (int j=i+1; j<N; ++j) {
                double e = m.el(j, i);
                m.add_row(j, e*s, i);
                inv.add_row(j, e*s, i);
            }
        }

        // reduce the matrix to diagonal
        for (int i=N-1; i>=0; --i) {
            double s = -1/m.el(i, i);

            for (int j=i-1; j>=0; --j) {
                double e = m.el(j, i);
                m.add_row(j, e*s, i);
                inv.add_row(j, e*s, i);
            }
        }

        // make the matrix an identity
        for (int i=0; i<N; ++i) {
            double e = 1/m.el(i, i);
            m.multiply_row(i, e);
            inv.multiply_row(i, e);
        }

        return inv;
    }

    void swap_rows(int i, int j) {
        double t;
        for (int k=0; k<N; ++k) {
            t = this->el(i, k);
            this->mut_el(i, k) = this->el(j, k);
            this->mut_el(j, k) = t;
        }
    }

    void add_row(int i, double alpha, int j) {
        for (int k=0; k<N; ++k) {
            this->mut_el(i, k) += alpha * this->el(j, k);
        }
    }

    void multiply_row(int i, double alpha) {
        for (int k=0; k<N; ++k) {
            this->mut_el(i, k) *= alpha;
        }
    }

    static Matrix<N> identity() {
        Matrix<N> m;
        for (int i=0; i<N; ++i)
            for (int j=0; j<N; ++j) {
                if (i == j)
                    m.mut_el(i, j) = 1.0;
                else
                    m.mut_el(i, j) = 0.0;
            }

        return m;
    }

    static Matrix<N> zeros() {
        Matrix<N> m;
        for (int i=0; i<N; ++i)
            for (int j=0; j<N; ++j) {
                m.mut_el(i, j) = 0.0;
            }

        return m;
    }

    void print() {
        for (int i=0; i<N; ++i) {
            for (int j=0; j<N; ++j)
                std::cout << el(i, j) << " ";
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};


#endif // MATRIX_H
