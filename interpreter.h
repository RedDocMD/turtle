#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

#include <memory>
#include <sstream>
#include <string>

#include "turtle.h"

class Interpreter {
  enum class CommandType {
    Fd,
    Bk,
    Rt,
    Lt,
    Repeat,
    Error,
  };

  static CommandType interpret_command_type(std::stringstream &ss);
  static std::unique_ptr<Operation> interpret_single(std::stringstream &ss);
  static std::unique_ptr<RepeatOperation> interpret_repeat(
      std::stringstream &ss, int cnt);

 public:
  static std::unique_ptr<Operation> interpret(const std::string &command);
};

#endif  // __INTERPRETER_H__
