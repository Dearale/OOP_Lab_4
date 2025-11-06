#pragma once

#include "figure.h"
#include <memory>
#include <vector>

template <class T>
class Figures {
  public:
    Figures() : Figures(1) {}
    Figures(const size_t &n) : size(0), capacity(n) {
        array = std::make_shared<T[]>(capacity);
    }

    Figures(const std::initializer_list<std::shared_ptr<T>> &t) : Figures(t.size()) {
        for (const auto &fig : t) {
            array[size++] = *fig;
        }
    }

    void printCenterForEachFigure() {
      for (size_t i = 0; i < size; i++) {
          std::cout << deref(array[i]) << "Геометрический центр: " << deref(array[i]).calcGeometricCenter() << "\n\n";
      }
    }

    void addFigure(T fig) {
        if (size >= capacity) {
            resize();
        }
        array[size++] = std::move(fig);
    }
    T operator[](size_t index) const{
        return array[index];
    }


    void resize() {
        if (capacity <= 0) {
            capacity = 1;
        }
        capacity *= 2;
        std::shared_ptr<T[]> tmp = std::make_shared<T[]>(capacity);
        for (size_t i = 0; i < size; ++i) {
            tmp[i] = std::move(array[i]);
        }

        array = std::move(tmp);
    }

    void printAreaForEachFigure() {
      for (size_t i = 0; i < size; i++) {
          std::cout << deref(array[i]) << "Площадь фигуры: " << deref(array[i]).calcArea() << "\n\n";
      }
    }

    void printCenterAndAreaForEachFigure() {
      for (size_t i = 0; i < size; i++) {
          std::cout << deref(array[i]) << "Геометрический центр: " << deref(array[i]).calcGeometricCenter() << '\n';
          std::cout << "Площадь фигуры: " << deref(array[i]).calcArea() << "\n\n";
      }
    }

    double calcTotalArea() {
        double s = 0;
        for (size_t i = 0; i < size; i++) {
            s += deref(array[i]).calcArea();
        }
        return s;
    }

    void deleteFigure(int index) {
        if (index < 0 || index >= size) {
          return;
        }

        for (size_t i = index; i < size - 1; i++) {
            array[i] = std::move(array[i + 1]);
        }

        size--;
    }
    
    size_t getSize() const { return size; }


    template <typename U>
    auto& deref(U& obj) {
        if constexpr (std::is_pointer_v<U> || requires { obj.operator->(); })
            return *obj;
        else
            return obj;
    }

  private:
    std::shared_ptr<T[]> array;
    size_t size = 0;
    size_t capacity = 1;
};