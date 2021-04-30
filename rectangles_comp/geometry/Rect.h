#pragma once
#include "Segment.h"
const int RECT_POINTS_COUNT = 4;
const int RECT_EDGES_COUNT = 4;

// Класс прямоугольника
class Rect {
public:
    // Массив точек прямоугольника
    Point** points = new Point*[RECT_POINTS_COUNT];

    // Массив отрезков, составляющих грани
    Segment** edges = new Segment*[RECT_EDGES_COUNT];

    // Проверка корректности прямоугольника
    bool correct_check(Point&, Point&, Point&, Point&);

    // Конструктор
    Rect(Point* = new Point(0, 0), Point* = new Point(0, 1), Point* = new Point(1, 1), Point* = new Point(1, 0));
    
    // Конструктор
    Rect(double*);

    // Пересекаются ли прямоугольники
    static bool are_rects_intersect(Rect &r1, Rect &r2) {
        Rect rects[2] = { r1, r2 };
        
        if (r1 == r2) return true;

        for (int i = 0; i < 2; i++) {
            for (int e1 = 0; e1 < RECT_EDGES_COUNT; e1++) {
                for (int e2 = 0; e2 < RECT_EDGES_COUNT; e2++) {
                    if (rects[i].edges[e1]->is_intersect(rects[1 - i].edges[e2])) return true;
                }
            }
        }

        int intersection_counter = 0;
        for (int i = 0; i < 2; i++) {
            for (int p1 = 0; p1 < RECT_POINTS_COUNT; p1++) {
                intersection_counter = 0;
                for (int p2 = 0; p2 < RECT_POINTS_COUNT; p2++) {
                    Segment segment(*rects[i].points[p1], *rects[1-i].points[p2]);

                    for (int e = 0; e < RECT_POINTS_COUNT; e++) {
                        if (Segment(*rects[i].points[p1], *rects[1 - i].points[p2]).is_intersect(rects[1 - i].edges[e])) intersection_counter++;
                    }
                }
                if (intersection_counter == 8) return true;
            }
        }

        return false;
    }

    // Пересекаются ли прямоугольники
    bool are_intersect(Rect&);

    // Перегрузка оператора =
    Rect& operator=(const Rect& rect) {
        for (int i = 0; i < RECT_POINTS_COUNT; i++) {
            edges[i] = rect.edges[i];
            points[i] = rect.points[i];
        }

        return *this;
    }

    // Перегрузка оператора ==
    bool operator==(Rect &other) {
        int counter = 0;

        for (int i = 0; i < RECT_POINTS_COUNT; i++) {
            if (this->points[i] == other.points[i]) counter++;
        }

        return counter == 4;
    }
};
