#include "Rect.h"

bool Rect::correct_check(Point p1, Point p2, Point p3, Point p4) {
    if (!(edges[0]->p2 == edges[1]->p1 && edges[1]->p2 == edges[2]->p1 && edges[2]->p2 == edges[3]->p1 && edges[3]->p2 == edges[0]->p1)) return false;

    if (!(edges[0]->is_perpendicular(*edges[1]) && edges[1]->is_perpendicular(*edges[2]) && edges[2]->is_perpendicular(*edges[3]))) return false;

    return true;
}

Rect::Rect(const Point p0, const Point p1, const Point p2, const Point p3) : points{p0, p1, p2, p3} {

    edges[0] = new Segment(points[0], points[1]);
    edges[1] = new Segment(points[1], points[2]);
    edges[2] = new Segment(points[2], points[3]);
    edges[3] = new Segment(points[3], points[0]);

    if (!Rect::correct_check(points[0], points[1], points[2], points[3])) throw;  // TODO

}

Rect::Rect(double c0[2], double c1[2], double c2[2], double c3[2]) : Rect(Point(c0), Point(c1), Point(c2), Point(c3)) {}

Rect::Rect(double* c[4]): Rect(c[0], c[1], c[2], c[3]) {}

bool Rect::is_intersect_line(const Line l) {
    return is_line_intersect_rectangle(*this, l);
}

bool Rect::are_intersect(const Rect r) {
    return are_rects_intersect(*this, r);
}
