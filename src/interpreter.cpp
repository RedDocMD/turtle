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

#include "interpreter.h"

#include <boost/algorithm/string.hpp>
#include <boost/assert.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/log/trivial.hpp>

std::unique_ptr<Operation> Interpreter::interpret(const std::string &command) {
  auto comm = command;
  boost::trim(comm);
  std::stringstream ss(comm);

  return interpret_single(ss);
}

Interpreter::CommandType Interpreter::interpret_command_type(
    std::stringstream &ss) {
  std::string comm_name;
  ss >> comm_name;
  if (comm_name == "FD")
    return CommandType::Fd;
  else if (comm_name == "BK")
    return CommandType::Bk;
  else if (comm_name == "RT")
    return CommandType::Rt;
  else if (comm_name == "LT")
    return CommandType::Lt;
  else if (comm_name == "REPEAT")
    return CommandType::Repeat;
  else if (comm_name == "CLS")
    return CommandType::Cls;
  else if (comm_name == "PEN")
    return CommandType::Pen;
  else
    return CommandType::Error;
}

std::unique_ptr<Operation> Interpreter::interpret_single(
    std::stringstream &ss) {
  try {
    auto type = interpret_command_type(ss);
    if (type == CommandType::Error) return {};
    if (type == CommandType::Cls)
      return std::make_unique<ClearScreenOperation>();

    std::string tok;
    ss >> tok;
    if (*tok.rbegin() == ',' || *tok.rbegin() == ')') {
      tok.pop_back();
      ss.unget();
    }
    BOOST_LOG_TRIVIAL(debug) << "Command number: \"" << tok << "\"";
    switch (type) {
      case CommandType::Fd: {
        int amt = boost::lexical_cast<int>(tok);
        return std::make_unique<ForwardOperation>(amt);
      }
      case CommandType::Bk: {
        int amt = boost::lexical_cast<int>(tok);
        return std::make_unique<BackwardOperation>(amt);
      }
      case CommandType::Rt: {
        int angle = boost::lexical_cast<int>(tok);
        return std::make_unique<RightTurnOperation>(angle);
      }
      case CommandType::Lt: {
        int angle = boost::lexical_cast<int>(tok);
        return std::make_unique<LeftTurnOperation>(angle);
      }
      case CommandType::Pen:
        if (tok == "UP")
          return std::make_unique<PenOperation>(PenOperationType::PutUp);
        else if (tok == "DOWN")
          return std::make_unique<PenOperation>(PenOperationType::PutDown);
        else
          return {};
      default:
        BOOST_ASSERT_MSG(type == CommandType::Repeat,
                         "Expected type to be repeat");
    }

    // Handle repeat
    int cnt = boost::lexical_cast<int>(tok);
    return interpret_repeat(ss, cnt);
  } catch (boost::bad_lexical_cast &err) {
    BOOST_LOG_TRIVIAL(error) << "invalid number: " << err.what();
    return {};
  }
}

std::unique_ptr<RepeatOperation> Interpreter::interpret_repeat(
    std::stringstream &ss, int cnt) {
  char c;
  std::vector<std::unique_ptr<Operation>> ops;

  ss >> std::skipws;
  ss >> c;
  if (c != '(') return {};
  while (true) {
    auto op = interpret_single(ss);
    if (!op) return {};
    ops.push_back(std::move(op));
    ss >> std::skipws;
    ss >> c;
    if (c == ')')
      return std::make_unique<RepeatOperation>(cnt, std::move(ops));
    else if (c != ',')
      return {};
  }
}
