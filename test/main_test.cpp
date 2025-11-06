#include <gtest/gtest.h>
#include <sstream>
#include <memory>
#include <cmath>

#include "../include/point.h"
#include "../include/figure.h"
#include "../include/diamond.h"
#include "../include/pentagon.h"
#include "../include/trapezoid.h"
#include "../include/figures.h"

template <typename T>
static ::testing::AssertionResult PointsNear(const Point<T>& a, const Point<T>& b, double eps = 1e-9) {
    if (std::fabs(a[0] - b[0]) < eps && std::fabs(a[1] - b[1]) < eps) return ::testing::AssertionSuccess();
    return ::testing::AssertionFailure()
        << "Points differ: (" << a[0] << "," << a[1] << ") vs ("
        << b[0] << "," << b[1] << "), eps=" << eps;
}

TEST(PointTest, IndexAndIO) {
    Point<double> p(1.5, -2.0);
    EXPECT_DOUBLE_EQ(p[0], 1.5);
    EXPECT_DOUBLE_EQ(p[1], -2.0);

    p[0] = 3.0; p[1] = 4.0;
    EXPECT_DOUBLE_EQ(p[0], 3.0);
    EXPECT_DOUBLE_EQ(p[1], 4.0);

    std::stringstream ss;
    ss << p;
    EXPECT_NE(ss.str().find("(3"), std::string::npos);
    EXPECT_NE(ss.str().find("4"), std::string::npos);

    std::stringstream in("(5 6)"); // Ваша перегрузка считывает два числа, скобки игнорируются потоком как обычные символы
    // Лучше использовать просто "5 6"
    std::stringstream in2("5 6");
    Point<int> pi;
    in2 >> pi;
    EXPECT_EQ(pi[0], 5);
    EXPECT_EQ(pi[1], 6);
}

TEST(DiamondTest, AreaAndCenter) {
    // Ромб (алмаз) с вершинами на осях: площадь = 2, центр = (0,0)
    Diamond<double> d{ { {0,1}, {1,0}, {0,-1}, {-1,0} } };

    EXPECT_NEAR(d.calcArea(), 2.0, 1e-9);
    EXPECT_NEAR(static_cast<double>(d), 2.0, 1e-9);

    Point<double> c = d.calcGeometricCenter();
    EXPECT_TRUE(PointsNear(c, Point<double>(0.0, 0.0)));
}

TEST(DiamondTest, Equality) {
    Diamond<int> a{ { {0,0}, {2,1}, {0,2}, {-2,1} } };
    Diamond<int> b{ { {0,0}, {2,1}, {0,2}, {-2,1} } };
    EXPECT_TRUE(a == b);
}

TEST(TrapezoidTest, AreaAndCenter) {
    // Равнобочная трапеция: A(0,0) B(4,0) C(3,2) D(1,2)
    // Площадь = (a + b)/2 * h = (4 + 2)/2 * 2 = 6
    Trapezoid<double> t{ { {0,0}, {4,0}, {3,2}, {1,2} } };
    EXPECT_NEAR(t.calcArea(), 6.0, 1e-9);
    EXPECT_NEAR(static_cast<double>(t), 6.0, 1e-9);

    // Центроида многоугольника для симметричной трапеции лежит на x=2 и где-то по высоте
    Point<double> c = t.calcGeometricCenter();
    EXPECT_NEAR(c[0], 2.0, 1e-9);
    EXPECT_NEAR(c[1], 0.8888888888, 1e-9);
}

TEST(PentagonTest, AreaAndCenter) {
    // Выпуклый пентагон без самопересечений
    // P0(0,0), P1(2,0), P2(3,1), P3(1.5,3), P4(-0.5,1)
    Pentagon<double> p{ { {0,0}, {2,0}, {3,1}, {1.5,3}, {-0.5,1} } };

    // Площадь по шнуровке заранее посчитана: 6.0
    EXPECT_NEAR(p.calcArea(), 6.25, 1e-9);

    // Для этой фигуры центр масс примерно (1.166666..., 1.333333...)
    Point<double> c = p.calcGeometricCenter();
    EXPECT_NEAR(c[0], 1.24666666666666, 1e-9);
    EXPECT_NEAR(c[1], 1.17333333333333, 1e-9);
}

TEST(FiguresArrayTest, AddResizeAndTotalArea) {
    // Начальная емкость мала, чтобы спровоцировать resize()
    Figures<Trapezoid<double>> arr(2);

    Trapezoid<double> t1{ { {0,0}, {4,0}, {3,2}, {1,2} } }; // area 6
    Trapezoid<double> t2{ { {0,0}, {2,0}, {1.5,1}, {0.5,1} } }; // a=2,b=1,h=1 => 1.5
    Trapezoid<double> t3{ { {0,0}, {6,0}, {4,2}, {2,2} } }; // a=6,b=2,h=2 => 8

    arr.addFigure(std::move(t1));
    arr.addFigure(std::move(t2));
    // Здесь должен сработать resize() с перемещением
    arr.addFigure(std::move(t3));

    EXPECT_EQ(arr.getSize(), static_cast<size_t>(3));
    EXPECT_NEAR(arr.calcTotalArea(), 6.0 + 1.5 + 8.0, 1e-9);
}

TEST(FiguresArrayTest, DeleteByIndexShiftsLeft) {
    Figures<Diamond<double>> arr(2);

    Diamond<double> d1{ { {0,1}, {1,0}, {0,-1}, {-1,0} } }; // area 2
    Diamond<double> d2{ { {0,2}, {2,0}, {0,-2}, {-2,0} } }; // area 8
    Diamond<double> d3{ { {0,3}, {3,0}, {0,-3}, {-3,0} } }; // area 18

    arr.addFigure(std::move(d1));
    arr.addFigure(std::move(d2));
    arr.addFigure(std::move(d3));
    EXPECT_EQ(arr.getSize(), static_cast<size_t>(3));
    EXPECT_NEAR(arr.calcTotalArea(), 2.0 + 8.0 + 18.0, 1e-9);

    // Удаляем второй элемент (индекс 1)
    arr.deleteFigure(1);
    EXPECT_EQ(arr.getSize(), static_cast<size_t>(2));

    // Оставшиеся площади: 2 и 18
    EXPECT_NEAR(arr.calcTotalArea(), 2.0 + 18.0, 1e-9);
}

TEST(StreamIoTest, FigureOutStreamHasVerticesAndAreaUsage) {
    Diamond<double> d{ { {0,1}, {1,0}, {0,-1}, {-1,0} } }; // area 2
    std::ostringstream os;
    os << d;
    std::string s = os.str();

    // Вывод должен содержать заголовок и координаты
    EXPECT_NE(s.find("Точки фигуры"), std::string::npos);
    EXPECT_NE(s.find("(0, 1)"), std::string::npos);
    EXPECT_NE(s.find("(-1, 0)"), std::string::npos);

    // Проверим явное приведение к double
    EXPECT_NEAR(static_cast<double>(d), 2.0, 1e-9);
}

template <typename T>
static ::testing::AssertionResult Near(double a, double b, double eps = 1e-9) {
    if (std::fabs(a - b) < eps) return ::testing::AssertionSuccess();
    return ::testing::AssertionFailure()
        << "Expected near: " << b << " got " << a << " (eps=" << eps << ")";
}

template <typename T>
static ::testing::AssertionResult PNear(const Point<T>& a, const Point<T>& b, double eps = 1e-9) {
    if (std::fabs(a[0] - b[0]) < eps && std::fabs(a[1] - b[1]) < eps) return ::testing::AssertionSuccess();
    return ::testing::AssertionFailure()
        << "Points differ: (" << a[0] << "," << a[1] << ") vs ("
        << b[0] << "," << b[1] << "), eps=" << eps;
}

// --- ЧТЕНИЕ ИЗ ПОТОКА ---

TEST(StreamInTest, ReadTrapezoidFromIStream) {
    // Формат ввода: просто четыре пары координат
    std::istringstream is("0 0  4 0  3 2  1 2");
    Trapezoid<double> t; // должен вызвать Figure(numOfPoints) и затем read()
    is >> t;
    EXPECT_FALSE(is.fail());

    // Площадь известна: 6
    EXPECT_TRUE(Near<double>(t.calcArea(), 6.0));
}

TEST(StreamInTest, ReadPentagonFromIStream) {
    std::istringstream is("0 0  2 0  3 1  1.5 3  -0.5 1");
    Pentagon<double> p;
    is >> p;
    EXPECT_FALSE(is.fail());
    EXPECT_TRUE(Near<double>(p.calcArea(), 6.25));
}

// --- ЗНАК ОРИЕНТИРОВАННОЙ ПЛОЩАДИ ---

TEST(AreaSignTest, ReversedOrderFlipsSign) {
    // Выпуклый ромб
    Diamond<double> d_ccw{ { {0,1}, {1,0}, {0,-1}, {-1,0} } }; // CCW (по умолч.)
    // Реверс вершин — CW
    Diamond<double> d_cw{ { {-1,0}, {0,-1}, {1,0}, {0,1} } };

    double s1 = d_ccw.calcAreaSigned();
    double s2 = d_cw.calcAreaSigned();

    EXPECT_LT(s1, 0.0);
    EXPECT_GT(s2, 0.0);
    EXPECT_TRUE(Near<double>(std::abs(s1), std::abs(s2)));
    EXPECT_TRUE(Near<double>(d_ccw.calcArea(), d_cw.calcArea()));
    EXPECT_TRUE(Near<double>(static_cast<double>(d_ccw), static_cast<double>(d_cw)));
}

// --- НЕРАВЕНСТВО ---

TEST(EqualityTest, NotEqualIfAnyVertexDiffers) {
    Trapezoid<double> a{ { {0,0}, {4,0}, {3,2}, {1,2} } };
    Trapezoid<double> b{ { {0,0}, {4,0}, {3,2.1}, {1,2} } };
    EXPECT_FALSE(a == b);
}

// --- getNumOfPoints() ---

TEST(NumPointsTest, EachDerivedReportsCorrectVertexCount) {
    Diamond<int> d;
    Trapezoid<int> t;
    Pentagon<int> p;
    EXPECT_EQ(d.getNumOfPoints(), 4);
    EXPECT_EQ(t.getNumOfPoints(), 4);
    EXPECT_EQ(p.getNumOfPoints(), 5);
}

// --- Figures<T> ПУСТОЙ/УДАЛЕНИЕ/РЕСАЙЗ ---

TEST(FiguresTest, EmptyArrayTotalAreaIsZero) {
    Figures<Diamond<double>> arr(2);
    EXPECT_EQ(arr.getSize(), static_cast<size_t>(0));
    EXPECT_TRUE(Near<double>(arr.calcTotalArea(), 0.0));
}

TEST(FiguresTest, DeleteInvalidIndexNoCrashNoChange) {
    Figures<Trapezoid<double>> arr(2);
    Trapezoid<double> t{ { {0,0}, {4,0}, {3,2}, {1,2} } }; // 6
    arr.addFigure(std::move(t));
    EXPECT_EQ(arr.getSize(), static_cast<size_t>(1));
    arr.deleteFigure(-1); // игнор
    EXPECT_EQ(arr.getSize(), static_cast<size_t>(1));
    arr.deleteFigure(42); // игнор
    EXPECT_EQ(arr.getSize(), static_cast<size_t>(1));
    EXPECT_TRUE(Near<double>(arr.calcTotalArea(), 6.0));
}

TEST(FiguresTest, SmallInitialCapacityTriggersResizeAndKeepsData) {
    Figures<Diamond<double>> arr(1); // маленькая емкость
    Diamond<double> d1{ { {0,1}, {1,0}, {0,-1}, {-1,0} } };   // area 2
    Diamond<double> d2{ { {0,2}, {2,0}, {0,-2}, {-2,0} } };   // area 8
    arr.addFigure(std::move(d1));
    arr.addFigure(std::move(d2)); // должен сработать resize() с move-операциями
    EXPECT_EQ(arr.getSize(), static_cast<size_t>(2));
    EXPECT_TRUE(Near<double>(arr.calcTotalArea(), 10.0));
}

TEST(FiguresTest, DeleteMiddleAndShiftLeft) {
    Figures<Pentagon<double>> arr(2);
    Pentagon<double> p1{ { {0,0}, {2,0}, {3,1}, {1.5,3}, {-0.5,1} } }; // 6
    Pentagon<double> p2{ { {0,0}, {4,0}, {5,1}, {2.5,4}, {-1,1} } };   // побольше
    Pentagon<double> p3{ { {0,0}, {1,0}, {1.2,0.5}, {0.5,1.5}, {-0.3,0.6} } }; // поменьше
    arr.addFigure(std::move(p1));
    arr.addFigure(std::move(p2));
    arr.addFigure(std::move(p3));

    double total_before = arr.calcTotalArea();
    ASSERT_EQ(arr.getSize(), static_cast<size_t>(3));

    arr.deleteFigure(1); // удалить средний
    EXPECT_EQ(arr.getSize(), static_cast<size_t>(2));

    // теперь массив содержит бывшие [0] и [2]
    double expected = total_before - Pentagon<double>{ { {0,0}, {4,0}, {5,1}, {2.5,4}, {-1,1} } }.calcArea();
    EXPECT_TRUE(Near<double>(arr.calcTotalArea(), expected));
}

// --- Вывод в поток ---

TEST(StreamOutTest, PrintsVerticesHumanReadable) {
    Diamond<double> d{ { {0,1}, {1,0}, {0,-1}, {-1,0} } };
    std::ostringstream os;
    os << d;
    std::string out = os.str();
    EXPECT_NE(out.find("Точки фигуры"), std::string::npos);
    EXPECT_NE(out.find("(0, 1)"), std::string::npos);
    EXPECT_NE(out.find("(-1, 0)"), std::string::npos);
}

// --- Суммирование через приведение к double ---

TEST(ConversionDoubleTest, SumAreasViaStaticCast) {
    Trapezoid<double> t1{ { {0,0}, {4,0}, {3,2}, {1,2} } }; // 6
    Trapezoid<double> t2{ { {0,0}, {2,0}, {1.5,1}, {0.5,1} } }; // 1.5
    std::vector<Trapezoid<double>> v;
    v.push_back(std::move(t1));
    v.push_back(std::move(t2));

    double sum = 0.0;
    for (const auto& x : v) sum += static_cast<double>(x);
    EXPECT_TRUE(Near<double>(sum, 7.5));
}

// --- Геометрический центр для простой симметрии ---

TEST(CentroidTest, DiamondAtOriginHasZeroCentroid) {
    Diamond<double> d{ { {0,2}, {2,0}, {0,-2}, {-2,0} } };
    auto c = d.calcGeometricCenter();
    EXPECT_TRUE(PNear<double>(c, Point<double>(0.0, 0.0)));
}