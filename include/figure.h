#pragma once

#include "point.h"
#include <initializer_list>
#include <iostream>
#include <memory>
#include <vector>

template<Scalar T>
class Figure {
  protected:
    Figure() = default;
    Figure(int numOfPoints) {
        points.resize(numOfPoints);
        for (int i = 0; i < numOfPoints; ++i) {
            points[i] = std::make_unique<Point<T>>();
        }
    }
    Figure(const std::initializer_list<Point<T>> &t) {
        points.clear();
        points.reserve(t.size());
        for (const auto& p : t) {
            points.push_back(std::make_unique<Point<T>>(p));
        }
    }
    Figure(const Figure &other) {
        points.clear();
        points.reserve(other.points.size());
        for (const auto& p : other.points) {
            if (p)
                points.push_back(std::make_unique<Point<T>>(*p));
            else
                points.push_back(nullptr);
        }
    }
    Figure(Figure &&other) noexcept = default;
    Figure &operator=(const Figure &other) {
        if (this == &other)
            return *this;
        
        points.clear();
        points.reserve(other.points.size());
        for (const auto& p : other.points) {
            if (p)
                points.push_back(std::make_unique<Point<T>>(*p));
            else
                points.push_back(nullptr);
        }
        return *this;
    }
    Figure &operator=(Figure &&other) = default;

    std::istream& read(std::istream &is) {
        return readPoints(is, getNumOfPoints());
    }

    std::istream& readPoints(std::istream &is, int pointNum) {
        points.resize(pointNum);
        for (int i = 0; i < pointNum; i++) {
            points[i] = std::make_unique<Point<T>>();
            is >> *points[i];
        }
        return is;
    }

  public:
    bool operator==(const Figure &other) const {
        if (points.size() != other.points.size()) return false;
        for (size_t i = 0; i < points.size(); ++i) {
            if (!points[i] || !other.points[i])
                return false;

            if (!(*points[i] == *other.points[i]))
                return false;
        }
        return true;
    }

    Point<T> calcGeometricCenter() const {
        double a = calcAreaSigned();
        double cx = 0, cy = 0;
        for (int i = 0; i < points.size(); i++) {
            int j = (i + 1) % points.size();
            double cross =
                (*points[i])[0] * (*points[j])[1] - (*points[j])[0] * (*points[i])[1];
            cx += ((*points[i])[0] + (*points[j])[0]) * cross;
            cy += ((*points[i])[1] + (*points[j])[1]) * cross;
        }
        cx /= (6 * a);
        cy /= (6 * a);
        return Point<T>(cx, cy);
    }

    double calcArea() const { return std::abs(calcAreaSigned()); }

    double calcAreaSigned() const {
        double s = 0;
        for (size_t i = 0; i < points.size(); i++) {
            size_t j = (i + 1) % points.size();
            s += (*points[i])[0] * (*points[j])[1] - (*points[j])[0] * (*points[i])[1];
        }

        return s / 2;
    }

    explicit operator double() const { return calcArea(); }

    friend std::ostream &operator<<(std::ostream &os, const Figure &figure) {
        os << "Точки фигуры:\n";
        for (int i = 0; i < figure.points.size(); i++) {
            os << *figure.points[i] << ' ';
        }
        os << '\n';
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Figure &figure) {
        return figure.read(is);
    }


    virtual int getNumOfPoints() const = 0;
    
    virtual ~Figure() = default;
  private:
    std::vector<std::unique_ptr<Point<T>>> points;
};