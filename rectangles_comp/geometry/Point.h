#pragma once

class Point {
public:
    double x;
    double y;

    Point(double X = 0, double Y = 0);
    Point(double[2]);

    const bool operator==(const Point);
    const bool operator==(const Point) const;

    Point& operator=(const Point &other) {
        x = other.x;
        y = other.y;

        return *this;
    }
};
