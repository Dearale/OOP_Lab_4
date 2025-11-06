#pragma once

#include "figure.h"
#include "point.h"
#include <initializer_list>

template<Scalar T>
class Pentagon : public Figure<T> {
  public:
    Pentagon() : Figure<T>(numOfPoints) {}
    Pentagon(const std::initializer_list<Point<T>> &t) : Figure<T>(t) {}
    Pentagon(const Pentagon &other) : Figure<T>(other) {}
    Pentagon(Pentagon &&other) : Figure<T>(other) {}
    Pentagon &operator=(const Pentagon &other) {
        Figure<T>::operator=(other);
        return *this;
    }
    Pentagon &operator=(Pentagon &&other) {
        Figure<T>::operator=(other);
        return *this;
    }
    bool operator==(const Pentagon &other) const {
        return Figure<T>::operator==(other);
    }

    static constexpr int numOfPoints = 5;

    int getNumOfPoints() const override { return numOfPoints; }
};