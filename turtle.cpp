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

void ForwardOperation::write(std::ostream &os) const { os << "FD " << amt; }

void BackwardOperation::action(Turtle &turtle) const {
  double old_x = turtle.get_x();
  double old_y = turtle.get_y();
  double theta = static_cast<double>(turtle.get_angle()) * M_PI / 180.0;

  double new_x = old_x - Turtle::SCALE_FACTOR * amt * sin(theta);
  double new_y = old_y + Turtle::SCALE_FACTOR * amt * cos(theta);

  turtle.set_x(new_x);
  turtle.set_y(new_y);
}

void BackwardOperation::write(std::ostream &os) const { os << "BK " << amt; }

void RightTurnOperation::action(Turtle &turtle) const {
  int old_angle = turtle.get_angle();
  int new_angle = old_angle + angle;
  turtle.set_angle(new_angle);
}

void RightTurnOperation::write(std::ostream &os) const { os << "RT " << angle; }

void LeftTurnOperation::action(Turtle &turtle) const {
  int old_angle = turtle.get_angle();
  int new_angle = old_angle - angle;
  turtle.set_angle(new_angle);
}

void LeftTurnOperation::write(std::ostream &os) const { os << "LT " << angle; }

void RepeatOperation::action(Turtle &turtle) const {
  throw "don't call action on Repeat Operation\n";
}

void RepeatOperation::write(std::ostream &os) const {
  os << "REPEAT " << cnt << " (";
  for (const auto &op : ops) os << *op << ", ";
  os << ")";
}

std::ostream &operator<<(std::ostream &os, const Operation &op) {
  op.write(os);
  return os;
}
