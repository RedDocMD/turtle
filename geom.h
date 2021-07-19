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

#ifndef __GEOM_H__
#define __GEOM_H__

#include <ostream>

struct Point {
  double x, y;
  Point(double x, double y) : x{x}, y{y} {}
  bool operator==(const Point &ot) const { return x == ot.x && y == ot.y; }
  bool operator!=(const Point &ot) const { return x != ot.x || y != ot.y; }
};

std::ostream &operator<<(std::ostream &os, const Point &pt);

struct Line {
  Point start, end;
  Line(Point start, Point end) : start{start}, end{end} {}
};

#endif  // __GEOM_H__
