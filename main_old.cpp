// #include <iostream>
// #include <sstream>

// #include "include/point.h"
// #include "include/figure.h"
// #include "include/trapezoid.h"
// #include "include/diamond.h"
// #include "include/pentagon.h"
// #include "include/figures.h"

// static void printFigureInfo(const char* name, const Figure& f) {
//     std::cout << name << '\n' << f;
//     Point c = f.calcGeometricCenter();
//     std::cout << "Геометрический центр:" << c << "\n";
//     std::cout << "Площадь: " << static_cast<double>(f) << "\n\n";
// }

int main() {
    // // 1) Создание фигур через список инициализации (перегруженные конструкторы)
    // Trapezoid t1({ {0,0}, {4,0}, {3,2}, {1,2} });
    // Diamond d1({ {0,0}, {2,2}, {4,0}, {2,-2} });
    // Pentagon p1({ {0,1}, {0.951,0.309}, {0.588,-0.809},
    //                {-0.588,-0.809}, {-0.951,0.309} });

    // // 2) Вывод, центр и площадь (<<, calcGeometricCenter, operator double)
    // printFigureInfo("Trapezoid t1", t1);
    // printFigureInfo("Diamond d1", d1);
    // printFigureInfo("Pentagon p1", p1);

    // // 3) Чтение из потока (>>) через istringstream
    // std::istringstream inTrap("0 0 4 0 3 2 1 2");
    // Trapezoid t_in;
    // inTrap >> t_in;
    // printFigureInfo("Trapezoid t_in (Чтение >>)", t_in);

    // // 4) Копирование / перемещение / сравнение (==)
    // Trapezoid t_copy = t1;
    // std::cout << "t1 == t_copy ? " << (t1 == t_copy ? "true" : "false") << "\n";

    // Diamond d_move = std::move(d1);
    // std::cout << "Moved diamond area: " << static_cast<double>(d_move) << "\n\n";

    // // 5) Групповые операции
    // Figure* fA = new Trapezoid(t1);
    // Figure* fB = new Diamond(d_move);
    // Figure* fC = new Pentagon(p1);

    // Figures figs({ fA, fB, fC });

    // std::cout << "== Геометрические центры для каждой фигуры ==\n";
    // figs.printCenterForEachFigure();

    // std::cout << "\n== Площади для каждой фигуры ==\n";
    // figs.printAreaForEachFigure();

    // std::cout << "\n== Геометрические центры и площади для каждой фигуры ==\n";
    // figs.printCenterAndAreaForEachFigure();

    // // 6) Общая площадь
    // double total = figs.calcTotalArea();
    // std::cout << "\nОбщая площадь до удаления: " << total << "\n";

    // // 7) Удаление по индексу
    // std::cout << "Размер до удаления: " << figs.getSize() << "\n";
    // figs.deleteFigure(1);
    // std::cout << "Размер после удаления: " << figs.getSize() << "\n";

    // // Пересчитать суммарную площадь после удаления
    // double total_after = figs.calcTotalArea();
    // std::cout << "Общая площадь после удаления: " << total_after << "\n";
    
    return 0;
}
