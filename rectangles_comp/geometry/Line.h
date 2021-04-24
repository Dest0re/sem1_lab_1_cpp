#pragma once
#include "Point.h"

class Line {
private:
    // A*x + B*y + C = 0 
    struct line_equality {
        double a;
        double b;
        double c;
        double k;

        double subst(const Point p) {
            return (a * p.x) + (b * p.y) + c;
        }
    };

public:
    Point p1;
    Point p2;
    line_equality eq;

    bool correct_check();

    Line(const Point, const Point);

    static bool is_point_belongs(Line line, const Point p) {
        return line.eq.subst(p) == 0 ? true : false;
    }

    static bool is_perpendicular(Line l1, Line l2) {
        return (l1.eq.a * l2.eq.a) + (l1.eq.b * l2.eq.b) == 0;
    }

    static int point_position(const Line l, const Point p) {
        int position = int((p.x * l.eq.a) + (p.y * l.eq.b) + l.eq.c);
        if (position == 0) {
            return 0;
        }
        else {
            return position < 0 ? -1 : 1;
        }
    }

    static bool is_intersect(Line l1, Line l2) {
        return l1.point_position(l2.p1) != l1.point_position(l2.p2);
    }

    static bool points_position(Line l, Point points[4]) {
        int position = l.point_position(points[0]);
        for (int i = 1; i < 4; i++) {
            if (position == 0) {
                if (l.point_position(points[i]) != 0) {
                    position = l.point_position(points[i]);
                }
            }
            else if (l.point_position(points[i]) != position && l.point_position(points[i]) != 0) return 0;
        }
        return position;
    }

    bool is_point_belongs(const Point);

    bool is_perpendicular(const Line);

    int point_position(const Point);

    bool is_intersect(const Line);

    bool points_position(Point[4]);

};