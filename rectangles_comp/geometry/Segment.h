#pragma once
#include "Line.h"

class Segment : public Line {
public:
    Segment(Point p1, Point p2) : Line(p1, p2) {}
};
