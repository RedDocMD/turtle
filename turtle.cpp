#include "turtle.h"
#include <cmath>

void ForwardOperation::action(Turtle &turtle) const {
  double old_x = turtle.get_x();
  double old_y = turtle.get_y();
  double theta = static_cast<double>(turtle.get_angle()) * M_PI / 180.0;

  double new_x = old_x + Turtle::SCALE_FACTOR * amt * sin(theta);
  double new_y = old_y - Turtle::SCALE_FACTOR * amt * cos(theta);

  turtle.set_x(new_x);
  turtle.set_y(new_y);
}

void BackwardOperation::action(Turtle &turtle) const {
  double old_x = turtle.get_x();
  double old_y = turtle.get_y();
  double theta = static_cast<double>(turtle.get_angle()) * M_PI / 180.0;

  double new_x = old_x - Turtle::SCALE_FACTOR * amt * sin(theta);
  double new_y = old_y + Turtle::SCALE_FACTOR * amt * cos(theta);

  turtle.set_x(new_x);
  turtle.set_y(new_y);
}

void RightTurnOperation::action(Turtle &turtle) const {
  int old_angle = turtle.get_angle();
  int new_angle = old_angle + angle;
  turtle.set_angle(new_angle);
}

void LeftTurnOperation::action(Turtle &turtle) const {
  int old_angle = turtle.get_angle();
  int new_angle = old_angle - angle;
  turtle.set_angle(new_angle);
}

void RepeatOperation::action(Turtle &turtle) const {
  for (auto i = 0; i < cnt; ++i) {
    for (const auto &op : ops) {
      op->action(turtle);
    }
  }
}
