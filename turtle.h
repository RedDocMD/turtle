#ifndef __TURTLE_H__
#define __TURTLE_H__

class Turtle {
  int x;
  int y;
  double angle;

public:
  Turtle() : x{0}, y{0}, angle{0.0} {}
  int get_x() const { return x; }
  int get_y() const { return y; }
  double get_angle() const { return angle; }
};

#endif // __TURTLE_H__
