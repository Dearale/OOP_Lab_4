#pragma once

#include <cassert>
#include <cstddef>
#include <iostream>
#include <cmath>
#include <type_traits>

template<typename T>
concept Scalar = std::is_scalar_v<T>;

template<Scalar T>
class Point {
    public:
        Point() : x(0), y(0) {}
        Point(T x, T y) : x(x), y(y) {}

        T& operator[](size_t index) {
            assert((index == 0) || (index == 1));
            return (index == 0) ? x : y;
        }
        T operator[](size_t index) const{
            assert((index == 0) || (index == 1));
            return (index == 0) ? x : y;
        }

        friend std::istream& operator>>(std::istream& is, Point& p) {
            is >> p[0] >> p[1];
            return is;
        }
        friend std::ostream& operator<<(std::ostream& os, const Point& p) {
            os << '(' << p[0] << ", " << p[1] << ')';
            return os;
        }

        bool operator==(const Point &other) const {
            return x == other.x && y == other.y;
        }
    
    private:
        T x;
        T y;
};