#pragma once
#include "Segment.h"

class Rect {
public:
    Point points[4];

    Segment* edges[4];

    bool correct_check(Point, Point, Point, Point);

    Rect(const Point = Point(0, 0), const Point = Point(0, 1), const Point = Point(1, 1), const Point = Point(1, 0));
    Rect(double[2], double[2], double[2], double[2]);
    Rect(double*[2]);

    static bool is_line_intersect_rectangle(Rect r, Line l) {
        for (int i = 0; i < 4; i++) {
            if (r.edges[i]->is_intersect(l)) return true;
        }
        return false;
    }

    static bool are_rects_intersect(Rect r1, Rect r2) {
        Rect rects[2] = { r1, r2 };

        for (int i = 0; i < 2; i++) {
            for (int e = 0; e < 4; e++) {
                int r2_position = rects[i].edges[e]->points_position(rects[1 - i].points);
                if (r2_position != 0) {
                    int r1_position = rects[1 - i].edges[e]->points_position(rects[1 - i].points);
                    if (r2_position != r1_position) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    bool is_intersect_line(const Line);

    bool are_intersect(const Rect);
};
