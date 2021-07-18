#ifndef __GEOM_H__
#define __GEOM_H__

#include <ostream>

struct Point {
  double x, y;
  Point(double x, double y) : x{x}, y{y} {}
  bool operator==(const Point &ot) { return x == ot.x && y == ot.y; }
  bool operator!=(const Point &ot) { return x != ot.x || y != ot.y; }
};

std::ostream &operator<<(std::ostream &os, const Point &pt);

struct Line {
  Point start, end;
  Line(Point start, Point end) : start{start}, end{end} {}
};

#endif  // __GEOM_H__
