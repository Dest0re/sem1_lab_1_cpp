#pragma once
#include "Point.h"

// Класс прямой
class Line {
private:
    // Структура уравнения прямой
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
    // Первая точка
    Point p1;

    // Вторая точка
    Point p2;

    // Уравнение прямой
    line_equality eq;

    // Проверка прямой на кооректность
    bool correct_check();

    // Конструктор
    Line(const Point, const Point);

    // Метод, проверяющий, принадлежит ли точка прямой
    static bool is_point_belongs(Line &line, const Point &p) {
        return line.eq.subst(p) == 0 ? true : false;
    }

    // Метод, проверяющий, перпендикулярны ли прямые
    static bool is_perpendicular(Line &l1, Line &l2) {
        return (l1.eq.a * l2.eq.a) + (l1.eq.b * l2.eq.b) == 0;
    }

    // Метод, определяющий положение точки относительно прямой
    static int point_position(const Line &l, const Point &p) {
        int position = int((p.x * l.eq.a) + (p.y * l.eq.b) + l.eq.c);
        if (position == 0) {
            return 0;
        }
        else {
            return position < 0 ? -1 : 1;
        }
    }

    // Пересекаются ли прямые
    static bool is_intersect(Line &l1, Line &l2) {
        return l1.point_position(l2.p1) != l1.point_position(l2.p2);
    }

    // Определение позиции точек относительно прямой
    static bool points_position(Line &l, Point points[4]) {
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

    // Принадлежит ли точка прямой
    bool is_point_belongs(const Point);

    // Перпендикулярны ли прямые
    bool is_perpendicular(Line);

    // Позиция точки относительно прямой
    int point_position(const Point);

    // Пересекаются ли прямые
    bool is_intersect(const Line);

    // Позиция точек относительно прямой 
    bool points_position(Point[4]);

};