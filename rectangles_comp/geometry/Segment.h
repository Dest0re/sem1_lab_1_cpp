#pragma once
#include <utility>

#include "Line.h"

const double EPS = 1E-9;

class Segment : public Line {
private:
    double _det(double a, double b, double  c, double d) {
        return a * d - b * c;
    }

	bool _between(double a, double b, double c) {
		return std::min(a, b) <= c + EPS && c <= std::max(a, b) + EPS;
	}

	bool _intersect_1(double a, double b, double c, double d) {
		if (a > b)  std::swap(a, b);
		if (c > d)  std::swap(c, d);
		return std::max(a, c) <= std::min(b, d);
	}

public:
    Segment(Point &p1, Point &p2) : Line(p1, p2) {}

    bool is_intersect(Segment *other) {
        double zn = _det(this->eq.a, this->eq.b, other->eq.a, other->eq.b);

		if (zn != 0) {
			double x = -_det(this->eq.c, this->eq.b, other->eq.c, other->eq.b) * 1. / zn;
			double y = -_det(this->eq.a, this->eq.c, other->eq.a, other->eq.c) * 1. / zn;
			
			return _between(this->p1.x, this->p2.x, x) && _between(this->p1.y, this->p2.y, y)
				&& _between(other->p1.x, other->p2.x, x) && _between(other->p1.y, other->p2.y, y);
		}
		else
			return _det(this->eq.a, this->eq.c, other->eq.a, other->eq.c) == 0 && _det(this->eq.b, this->eq.c, other->eq.b, other->eq.c) == 0
			&& _intersect_1(this->p1.x, this->p2.x, other->p1.x, other->p2.x)
			&& _intersect_1(this->p1.y, this->p2.y, other->p1.y, other->p2.y);
    }
};
