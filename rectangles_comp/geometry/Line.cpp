#include "Line.h"

bool Line::correct_check() {
    return (eq.a == 0 && eq.b == 0) ? false : true;
}

Line::Line(const Point point1, const Point point2) : p1{ point1 }, p2{ point2 } {


    if (p1 == p2) {
        throw;  // TODO
    }

    eq.a = p1.y - p2.y;
    eq.b = p2.x - p1.x;

    if (!correct_check()) throw;  // TODO

    eq.c = (p1.x * p2.y) - (p2.x * p1.y);  // Строго говоря, скобки излишни и не влияют на порядок выполнения, однако они способствуют читаемости.
    eq.k = eq.a / eq.b;
}


bool Line::is_point_belongs(const Point p) {
    return is_point_belongs(*this, p);
}

bool Line::is_perpendicular(const Line l) {
    return is_perpendicular(*this, l);
}

int Line::point_position(const Point p) {
    return point_position(*this, p);
}

bool Line::is_intersect(const Line l) {
    return is_intersect(*this, l);
}

bool Line::points_position(Point points[4]) {
    return points_position(*this, points);
}