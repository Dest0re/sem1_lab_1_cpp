#include <stdexcept>

#include "Rect.h"
#include "Point.h"

bool Rect::correct_check(Point &p1, Point &p2, Point &p3, Point &p4) {
    if (p1 == p2 || p2 == p3 || p3 == p4 || p4 == p1) throw std::invalid_argument("The rectangle cannot exist");

    if (!(edges[0]->p2 == edges[1]->p1 && edges[1]->p2 == edges[2]->p1 && edges[2]->p2 == edges[3]->p1 && edges[3]->p2 == edges[0]->p1)) return false;

    if (!(edges[0]->is_perpendicular(*edges[1]) && edges[1]->is_perpendicular(*edges[2]) && edges[2]->is_perpendicular(*edges[3]))) return false;

    return true;
}

Rect::Rect(Point *p0, Point *p1, Point *p2, Point *p3) {
    points[0] = p0;
    points[1] = p1;
    points[2] = p2;
    points[3] = p3;


    edges[0] = new Segment(*points[0], *points[1]);
    edges[1] = new Segment(*points[1], *points[2]);
    edges[2] = new Segment(*points[2], *points[3]);
    edges[3] = new Segment(*points[3], *points[0]);

    if (!Rect::correct_check(*points[0], *points[1], *points[2], *points[3])) throw std::invalid_argument("A rectangle with such coordinates does not exist");
}

Rect::Rect(double* points) : Rect(new Point(points[0], points[1]), new Point(points[2], points[3]), new Point(points[4], points[5]), new Point(points[6], points[7])) {}

bool Rect::are_intersect(Rect &r) {
    return are_rects_intersect(*this, r);
}
