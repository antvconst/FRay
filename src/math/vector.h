#ifndef VECTOR_H
#define VECTOR_H

#include "cmath"
#include <cstdarg>
#include <iostream>

template<int N>
class Vector
{
public:
    double data[N];

    Vector() {}
    Vector(double x, ...) {
        std::va_list args;
        mut_el(0) = x;
        va_start(args, x);
        for (int i=1; i<N; ++i) {
            data[i] = va_arg(args, double);
        }
    }

    const double& el(int i) const {
        return data[i];
    }

    double& mut_el(int i) {
        return const_cast<double&>(el(i));
    }

    Vector<N> operator-() const {
        Vector<N> r;
        for (int i=0; i<N; ++i)
            r.mut_el(i) = el(i);
        return r;
    }

    Vector<N> operator+(const Vector<N>& v) const {
        Vector<N> r;
        for (int i=0; i<N; ++i)
            r.mut_el(i) = el(i) + v.el(i);
        return r;
    }
    Vector<N> operator-(const Vector<N>& v) const {
        Vector<N> r;
        for (int i=0; i<N; ++i)
            r.mut_el(i) = el(i) - v.el(i);
        return r;
    }
    Vector<N> operator*(double  alpha) const {
        Vector<N> r;
        for (int i=0; i<N; ++i)
            r.mut_el(i) = alpha*el(i);
        return r;
    }

    // Component-wise multiplication
    Vector<N> operator*(const Vector<N>& v) const {
        Vector<N> r;
        for (int i=0; i<N; ++i)
            r.mut_el(i) = el(i) * v.el(i);
        return r;
    }

    Vector<N> operator/(double alpha) const {
        return (*this)*(1/alpha);
    }

    double len() const {
        double s, t = 0;
        for (int i=0; i<N; ++i) {
            s = el(i);
            t += s*s;
        }
        return sqrt(t);
    }
    Vector<N> normalize() const {
        return (*this) / len();
    }

    void print() const {
        for (int i=0; i<N; ++i)
            std::cout << el(i) << " ";
        std::cout << std::endl;
    }
};

#endif // VECTOR_H
