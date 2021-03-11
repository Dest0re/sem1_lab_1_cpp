#include "Point.h"
Point::Point(double X, double Y) : x{ X }, y{ Y } {}

Point::Point(double c[2]) : Point(c[0], c[1]) {}

const bool Point::operator==(const Point other) {
    return other.x == x && other.y == y ? true : false;
}

const bool Point::operator==(const Point other) const {
    return other.x == x && other.y == y ? true : false;
}
