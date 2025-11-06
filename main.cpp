#include <iostream>
#include <memory>
#include <iomanip>
#include <iostream>
#include <memory>

#include "include/pentagon.h"
#include "include/trapezoid.h"
#include "include/diamond.h"
#include "include/figures.h"
#include "include/point.h"

using namespace std;

template<Scalar T>
void demonstrateFigures() {
    cout << "=== Демонстрация работы с фигурами (тип " << typeid(T).name() << ") ===" << endl;

    // Создание массива для хранения указателей на базовый класс Figure
    Figures<shared_ptr<Figure<T>>> figures;

    // Создание фигур с заранее заданными координатами
    cout << "\nСоздание фигур..." << endl;
    
    // Пятиугольник
    auto pentagon = make_shared<Pentagon<T>>(std::initializer_list<Point<T>>{
        Point<T>{0, 1}, 
        Point<T>{-1, 0}, 
        Point<T>{static_cast<T>(-0.5), -1}, 
        Point<T>{static_cast<T>(0.5), -1}, 
        Point<T>{1, 0}
    });
    figures.addFigure(pentagon);

    // Трапеция
    auto trapezoid = make_shared<Trapezoid<T>>(std::initializer_list<Point<T>>{
        Point<T>{0, 0}, 
        Point<T>{4, 0}, 
        Point<T>{3, 3}, 
        Point<T>{1, 3}
    });
    figures.addFigure(trapezoid);

    // Ромб
    auto diamond = make_shared<Diamond<T>>(std::initializer_list<Point<T>>{
        Point<T>{0, 2}, 
        Point<T>{2, 0}, 
        Point<T>{0, -2}, 
        Point<T>{-2, 0}
    });
    figures.addFigure(diamond);

    // Вывод информации о всех фигурах
    cout << "\n=== Информация о всех фигурах ===" << endl;
    figures.printCenterAndAreaForEachFigure();

    // Вывод только центров
    cout << "\n=== Геометрические центры фигур ===" << endl;
    figures.printCenterForEachFigure();

    // Вывод только площадей
    cout << "\n=== Площади фигур ===" << endl;
    figures.printAreaForEachFigure();

    // Общая площадь
    cout << "\n=== Общая площадь всех фигур ===" << endl;
    cout << "Суммарная площадь: " << figures.calcTotalArea() << endl;

    // Демонстрация приведения к double
    cout << "\n=== Приведение фигур к double (площадь) ===" << endl;
    for (size_t i = 0; i < figures.getSize(); i++) {
        double area = static_cast<double>(*figures[i]);
        cout << "Фигура " << i << ": " << area << endl;
    }

    // Демонстрация удаления фигуры
    cout << "\n=== Удаление фигуры с индексом 1 ===" << endl;
    figures.deleteFigure(1);
    cout << "После удаления осталось фигур: " << figures.getSize() << endl;
    figures.printCenterAndAreaForEachFigure();
}

template<Scalar T>
void demonstrateConcreteFigures() {
    cout << "\n=== Демонстрация работы с конкретными фигурами (Trapezoid) ===" << endl;
    
    // Создание массива конкретных фигур
    Figures<shared_ptr<Trapezoid<T>>> concreteFigures;

    // Добавление трапеций
    cout << "Добавление трапеций..." << endl;

    auto diamond = make_shared<Diamond<T>>(std::initializer_list<Point<T>>{
        Point<T>{0, 2}, 
        Point<T>{2, 0}, 
        Point<T>{0, -2}, 
        Point<T>{-2, 0}
    });

    auto t1 = make_shared<Trapezoid<T>>(std::initializer_list<Point<T>>{Point<T>{0, 0}, Point<T>{4, 0}, Point<T>{3, 3}, Point<T>{1, 3}});
    auto t2 = make_shared<Trapezoid<T>>(std::initializer_list<Point<T>>{Point<T>{1, 1}, Point<T>{5, 1}, Point<T>{4, 4}, Point<T>{2, 4}});
    auto t3 = make_shared<Trapezoid<T>>(std::initializer_list<Point<T>>{Point<T>{2, 2}, Point<T>{6, 2}, Point<T>{5, 5}, Point<T>{3, 5}});
    
    concreteFigures.addFigure(t1);
    concreteFigures.addFigure(t2);
    concreteFigures.addFigure(t3);

    cout << "Информация о трапециях:" << endl;
    concreteFigures.printCenterAndAreaForEachFigure();
    
    cout << "Общая площадь трапеций: " << concreteFigures.calcTotalArea() << endl;
    
    // Демонстрация сравнения фигур
    cout << "\n=== Сравнение фигур ===" << endl;
    cout << "t1 == t2: " << (t1 == t2 ? "true" : "false") << endl;
    cout << "t1 == t1: " << (t1 == t1 ? "true" : "false") << endl;
}

template<Scalar T>
void demonstrateCopyAndMove() {
    cout << "\n=== Демонстрация копирования и перемещения ===" << endl;
    
    // Создание оригинальной фигуры
    Diamond<T> original{Point<T>{0, 1}, Point<T>{1, 0}, Point<T>{0, -1}, Point<T>{-1, 0}};
    cout << "Оригинальный ромб:" << endl;
    cout << original << "Площадь: " << original.calcArea() << endl;
    
    // Копирование
    Diamond<T> copied = original;
    cout << "Скопированный ромб:" << endl;
    cout << copied << "Площадь: " << copied.calcArea() << endl;
    
    // Проверка равенства
    cout << "original == copied: " << (original == copied ? "true" : "false") << endl;
    
    // Перемещение
    Diamond<T> moved = std::move(original);
    cout << "Перемещенный ромб:" << endl;
    cout << moved << "Площадь: " << moved.calcArea() << endl;
}

template<Scalar T>
void demonstrateArrayResize() {
    cout << "\n=== Демонстрация увеличения емкости массива ===" << endl;
    
    Figures<shared_ptr<Figure<T>>> figures(2); // Начальная емкость 2
    
    cout << "Начальная емкость: 2" << endl;
    
    // Добавляем больше элементов, чем начальная емкость
    for (int i = 0; i < 5; i++) {
        auto pentagon = make_shared<Pentagon<T>>(std::initializer_list<Point<T>>{
            Point<T>{0.0 + i, 1}, 
            Point<T>{-1.0 + i, 0}, 
            Point<T>{-0.5 + i, -1}, 
            Point<T>{0.5 + i, -1}, 
            Point<T>{1.0 + i, 0}
        });
        figures.addFigure(pentagon);
        cout << "Добавлена фигура " << i << ", размер массива: " << figures.getSize() << endl;
    }
    
    cout << "Финальный размер массива: " << figures.getSize() << endl;
    cout << "Общая площадь: " << figures.calcTotalArea() << endl;
}

int main() {
    // cout << fixed << setprecision(2);
    
    // Демонстрация с типом double
    demonstrateFigures<double>();
    
    // Демонстрация с типом int
    cout << "\n\n";
    demonstrateFigures<int>();
    
    // Демонстрация работы с конкретными фигурами
    demonstrateConcreteFigures<double>();
    
    // Демонстрация копирования и перемещения
    demonstrateCopyAndMove<double>();
    
    // Демонстрация увеличения емкости массива
    demonstrateArrayResize<double>();

    return 0;
}