#ifndef __TURTLE_H__
#define __TURTLE_H__

#include "geom.h"
#include <memory>
#include <utility>
#include <vector>

class ForwardOperation;
class BackwardOperation;
class RightTurnOperation;
class LeftTurnOperation;

class Turtle {
  double x = 0;
  double y = 0;
  int angle = 0;

  friend class ForwardOperation;
  friend class BackwardOperation;
  friend class RightTurnOperation;
  friend class LeftTurnOperation;

public:
  Turtle() = default;
  double get_x() const { return x; }
  double get_y() const { return y; }
  int get_angle() const { return angle; }
  Point get_position() const { return {x, y}; }

  // 1 unit of LOGO corresponds to SCALE_FACTOR px
  constexpr static int SCALE_FACTOR = 5;

private:
  void set_x(double x) { this->x = x; }
  void set_y(double y) { this->y = y; }
  void set_angle(int angle) { this->angle = angle; }
};

class Operation {
public:
  virtual ~Operation() = default;
  virtual void action(Turtle &turtle) const = 0;
};

class ForwardOperation : public Operation {
  int amt;

public:
  explicit ForwardOperation(int amt) : amt{amt} {}
  ~ForwardOperation() = default;
  void action(Turtle &turtle) const override;
};

class BackwardOperation : public Operation {
  int amt;

public:
  explicit BackwardOperation(int amt) : amt{amt} {}
  ~BackwardOperation() = default;
  void action(Turtle &turtle) const override;
};

class RightTurnOperation : public Operation {
  int angle;

public:
  explicit RightTurnOperation(int angle) : angle{angle} {}
  ~RightTurnOperation() = default;
  void action(Turtle &turtle) const override;
};

class LeftTurnOperation : public Operation {
  int angle;

public:
  explicit LeftTurnOperation(int angle) : angle{angle} {}
  ~LeftTurnOperation() = default;
  void action(Turtle &turtle) const override;
};

class RepeatOperation : public Operation {
  int cnt;
  std::vector<std::unique_ptr<Operation>> ops;

public:
  explicit RepeatOperation(int cnt, std::vector<std::unique_ptr<Operation>> ops)
      : cnt{cnt}, ops(std::move(ops)) {}
  ~RepeatOperation() = default;
  void action(Turtle &turtle) const override;
};

#endif // __TURTLE_H__
