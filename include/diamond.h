#pragma once

#include "figure.h"
#include "point.h"
#include <initializer_list>

template<Scalar T>
class Diamond : public Figure<T> {
  public:
    Diamond() : Figure<T>(numOfPoints) {}
    Diamond(const std::initializer_list<Point<T>> &t) : Figure<T>(t) {}
    Diamond(const Diamond &other) : Figure<T>(other) {}
    Diamond(Diamond &&other) : Figure<T>(other) {}

    Diamond &operator=(const Diamond &other) {
        Figure<T>::operator=(other);
        return *this;
    }

    Diamond &operator=(Diamond &&other) {
        Figure<T>::operator=(other);
        return *this;
    }
    bool operator==(const Diamond &other) const {
        return Figure<T>::operator==(other);
    }

    static constexpr int numOfPoints = 4;

    int getNumOfPoints() const override { return numOfPoints; }
};