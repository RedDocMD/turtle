#include "turtle.h"
#include <cmath>

void ForwardOperation::action(Turtle &turtle) const {
  int old_x = turtle.get_x();
  int old_y = turtle.get_y();
  double theta = static_cast<double>(turtle.get_angle()) * M_PI / 180.0;

  int new_x = old_x + Turtle::SCALE_FACTOR * amt * sin(theta);
  int new_y = old_y - Turtle::SCALE_FACTOR * amt * cos(theta);

  turtle.set_x(new_x);
  turtle.set_y(new_y);
}

void RightTurnOperation::action(Turtle &turtle) const {
  int old_angle = turtle.get_angle();
  int new_angle = old_angle + angle;
  turtle.set_angle(new_angle);
}
