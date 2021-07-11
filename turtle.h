#ifndef __TURTLE_H__
#define __TURTLE_H__

#include <utility>

class ForwardOperation;
class RightTurnOperation;

class Turtle {
  int x = 0;
  int y = 0;
  int angle = 0;

  friend class ForwardOperation;
  friend class RightTurnOperation;

public:
  Turtle() = default;
  int get_x() const { return x; }
  int get_y() const { return y; }
  int get_angle() const { return angle; }
  std::pair<int, int> get_position() const { return {x, y}; }

  // 1 unit of LOGO corresponds to SCALE_FACTOR px
  constexpr static int SCALE_FACTOR = 5;

private:
  void set_x(int x) { this->x = x; }
  void set_y(int y) { this->y = y; }
  void set_angle(int angle) { this->angle = angle; }
};

class Operation {
public:
  virtual ~Operation() {}
  virtual void action(Turtle &turtle) const = 0;
};

class ForwardOperation : public Operation {
  int amt;

public:
  explicit ForwardOperation(int amt) : amt{amt} {}
  ~ForwardOperation() {}
  void action(Turtle &turtle) const override;
};

class RightTurnOperation : public Operation {
  int angle;

public:
  explicit RightTurnOperation(int angle) : angle{angle} {}
  ~RightTurnOperation() {}
  void action(Turtle &turtle) const override;
};

#endif // __TURTLE_H__
