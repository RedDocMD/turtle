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

#ifndef __TURTLE_H__
#define __TURTLE_H__

#include <memory>
#include <utility>
#include <vector>

#include "geom.h"

class ForwardOperation;
class BackwardOperation;
class RightTurnOperation;
class LeftTurnOperation;
class ClearScreenOperation;
class PenOperation;

enum class PenState {
  Up,
  Down,
};

class Turtle {
  double x = 0;
  double y = 0;
  int angle = 0;
  PenState state = PenState::Down;

  friend class ForwardOperation;
  friend class BackwardOperation;
  friend class RightTurnOperation;
  friend class LeftTurnOperation;
  friend class ClearScreenOperation;
  friend class PenOperation;

 public:
  Turtle() = default;
  [[nodiscard]] double get_x() const { return x; }
  [[nodiscard]] double get_y() const { return y; }
  [[nodiscard]] int get_angle() const { return angle; }
  [[nodiscard]] Point get_position() const { return {x, y}; }
  [[nodiscard]] bool is_pen_down() const { return state == PenState::Down; }

  // 1 unit of LOGO corresponds to SCALE_FACTOR px
  constexpr static int SCALE_FACTOR = 2;

 private:
  void set_x(double mx) { x = mx; }
  void set_y(double my) { y = my; }
  void set_angle(int mangle) { angle = mangle; }
  void set_pen_state(PenState xstate) { state = xstate; }
  void reset();
};

class Operation {
 public:
  virtual ~Operation() = default;
  virtual void action(Turtle &turtle) const = 0;
  virtual void write(std::ostream &os) const = 0;
};

std::ostream &operator<<(std::ostream &os, const Operation &op);

class ForwardOperation : public Operation {
  int amt;

 public:
  explicit ForwardOperation(int amt) : amt{amt} {}
  ~ForwardOperation() override = default;
  void action(Turtle &turtle) const override;
  void write(std::ostream &os) const override;
};

class BackwardOperation : public Operation {
  int amt;

 public:
  explicit BackwardOperation(int amt) : amt{amt} {}
  ~BackwardOperation() override = default;
  void action(Turtle &turtle) const override;
  void write(std::ostream &os) const override;
};

class RightTurnOperation : public Operation {
  int angle;

 public:
  explicit RightTurnOperation(int angle) : angle{angle} {}
  ~RightTurnOperation() override = default;
  void action(Turtle &turtle) const override;
  void write(std::ostream &os) const override;
};

class LeftTurnOperation : public Operation {
  int angle;

 public:
  explicit LeftTurnOperation(int angle) : angle{angle} {}
  ~LeftTurnOperation() override = default;
  void action(Turtle &turtle) const override;
  void write(std::ostream &os) const override;
};

class RepeatOperation : public Operation {
  int cnt;
  std::vector<std::unique_ptr<Operation>> ops;

 public:
  explicit RepeatOperation(int cnt, std::vector<std::unique_ptr<Operation>> ops)
      : cnt{cnt}, ops(std::move(ops)) {}
  ~RepeatOperation() override = default;
  void action(Turtle &turtle) const override;
  void write(std::ostream &os) const override;
  [[nodiscard]] int get_cnt() const { return cnt; }
  [[nodiscard]] const std::vector<std::unique_ptr<Operation>> &get_ops() const { return ops; }
};

class ClearScreenOperation : public Operation {
 public:
  ClearScreenOperation() = default;
  ~ClearScreenOperation() override = default;
  void action(Turtle &turtle) const override { turtle.reset(); }
  void write(std::ostream &os) const override { os << "CLS"; }
};

enum class PenOperationType {
  PutUp,
  PutDown,
};

class PenOperation : public Operation {
  PenOperationType type;

 public:
  explicit PenOperation(PenOperationType type) : type{type} {}
  ~PenOperation() override = default;
  void action(Turtle &turtle) const override;
  void write(std::ostream &os) const override;
};

#endif  // __TURTLE_H__
