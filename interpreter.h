#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

#include "turtle.h"
#include <memory>
#include <optional>
#include <regex>
#include <string>

class Interpreter {
  std::regex fd_reg{R"(FD (\d+))"};
  std::regex bk_reg{R"(BK (\d+))"};
  std::regex rt_reg{R"(RT (\d+))"};
  std::regex lt_reg{R"(LT (\d+))"};
  std::regex rep_reg{R"(REPEAT (\d+) \(([\s\w\d,]+)\))"};
  std::regex comma_sep{R"(,\s*)"};

public:
  std::optional<std::unique_ptr<Operation>> interpret(const std::string &command);
};

#endif // __INTERPRETER_H__
