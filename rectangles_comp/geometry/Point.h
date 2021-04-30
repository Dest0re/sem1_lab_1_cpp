#pragma once

// Класс точки
class Point {
public:
    // Координата X
    double x;

    // Координата Y
    double y;

    // Конструктор
    Point(double X = 0, double Y = 0);

    // Конструктор
    Point(double[2]);

    // Перегрузка оператора ==
    const bool operator==(const Point);
    const bool operator==(const Point) const;

    // Перегрузка оператора =
    Point& operator=(const Point&);
};
