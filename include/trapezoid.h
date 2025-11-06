#pragma once

#include "figure.h"
#include "point.h"
#include <initializer_list>

template<Scalar T>
class Trapezoid : public Figure<T> {
  public:
    Trapezoid() : Figure<T>(numOfPoints) {}
    Trapezoid(const std::initializer_list<Point<T>> &t) : Figure<T>(t) {}
    Trapezoid(const Trapezoid &other) : Figure<T>(other) {}
    Trapezoid(Trapezoid &&other) : Figure<T>(other) {}
    Trapezoid &operator=(const Trapezoid &other) {
        Figure<T>::operator=(other);
        return *this;
    }

    Trapezoid &operator=(Trapezoid &&other) {
        Figure<T>::operator=(other);
        return *this;
    }

    bool operator==(const Trapezoid &other) const {
        return Figure<T>::operator==(other);
    }

    static constexpr int numOfPoints = 4;

    int getNumOfPoints() const override { return numOfPoints; }
};