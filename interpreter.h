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
    Cls,
    Pen,
    Error,
  };

  static CommandType interpret_command_type(std::stringstream &ss);
  static std::unique_ptr<Operation> interpret_single(std::stringstream &ss);
  static std::unique_ptr<RepeatOperation> interpret_repeat(
      std::stringstream &ss, int cnt);

 public:
  Interpreter() = delete;
  Interpreter(const Interpreter &) = delete;
  Interpreter(Interpreter &&) = delete;
  ~Interpreter() = delete;
  static std::unique_ptr<Operation> interpret(const std::string &command);
};

#endif  // __INTERPRETER_H__
