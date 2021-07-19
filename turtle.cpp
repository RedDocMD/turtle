/*
 *   Turtle - A basic implementation of LOGO
 *   Copyright (C) 2021 Deep Majumder
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License along
 *   with this program; if not, write to the Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

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
