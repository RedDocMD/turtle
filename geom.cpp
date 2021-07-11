#include "geom.h"

std::ostream &operator<<(std::ostream &os, const Point &pt) {
  os << "(" << pt.x << ", " << pt.y << ")";
  return os;
}
