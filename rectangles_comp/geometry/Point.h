#pragma once
#include <iostream>

class Point {
public:
    const double x;
    const double y;

    Point(double X = 0, double Y = 0);
    Point(double[2]);

    const bool operator==(const Point);
    const bool operator==(const Point) const;
};
