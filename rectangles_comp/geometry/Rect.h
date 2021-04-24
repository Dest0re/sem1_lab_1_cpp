#pragma once
#include "Segment.h"

class Rect {
public:
    Point** points = new Point*[4];

    Segment** edges = new Segment*[4];

    bool correct_check(Point, Point, Point, Point);

    Rect(Point* = new Point(0, 0), Point* = new Point(0, 1), Point* = new Point(1, 1), Point* = new Point(1, 0));
    Rect(double*);

    ~Rect();

    static bool are_rects_intersect(Rect r1, Rect r2) {
        Rect rects[2] = { r1, r2 };
        
        if (r1 == r2) return true;

        for (int i = 0; i < 2; i++) {
            for (int e1 = 0; e1 < 4; e1++) {
                for (int e2 = 0; e2 < 4; e2++) {
                    if (rects[i].edges[e1]->is_intersect(rects[1 - i].edges[e2])) return true;
                }
            }
        }

        int intersection_counter = 0;
        for (int i = 0; i < 2; i++) {
            for (int p1 = 0; p1 < 4; p1++) {
                intersection_counter = 0;
                for (int p2 = 0; p2 < 4; p2++) {
                    Segment segment(*rects[i].points[p1], *rects[1-i].points[p2]);

                    for (int e = 0; e < 4; e++) {
                        if (Segment(*rects[i].points[p1], *rects[1 - i].points[p2]).is_intersect(rects[1 - i].edges[e])) intersection_counter++;
                    }
                }
                if (intersection_counter == 8) return true;
            }
        }

        return false;
    }

    //bool is_intersect_line(const Line);

    bool are_intersect(Rect&);

    Rect& operator=(const Rect& rect) {
        for (int i = 0; i < 4; i++) {
            edges[i] = rect.edges[i];
            points[i] = rect.points[i];
        }

        return *this;
    }

    bool operator==(Rect other) {
        int counter = 0;

        for (int i = 0; i < 4; i++) {
            if (this->points[i] == other.points[i]) counter++;
        }

        return counter == 4;
    }
};
