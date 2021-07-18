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
  [[nodiscard]] double get_x() const { return x; }
  [[nodiscard]] double get_y() const { return y; }
  [[nodiscard]] int get_angle() const { return angle; }
  [[nodiscard]] Point get_position() const { return {x, y}; }

  // 1 unit of LOGO corresponds to SCALE_FACTOR px
  constexpr static int SCALE_FACTOR = 2;

 private:
  void set_x(double mx) { x = mx; }
  void set_y(double my) { y = my; }
  void set_angle(int mangle) { angle = mangle; }
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

#endif  // __TURTLE_H__
