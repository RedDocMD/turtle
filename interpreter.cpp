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
  CommandType comm_type;
  std::string comm_name;
  ss >> comm_name;
  if (comm_name == "FD")
    comm_type = CommandType::Fd;
  else if (comm_name == "BK")
    comm_type = CommandType::Bk;
  else if (comm_name == "RT")
    comm_type = CommandType::Rt;
  else if (comm_name == "LT")
    comm_type = CommandType::Lt;
  else if (comm_name == "REPEAT")
    comm_type = CommandType::Repeat;
  else
    comm_type = CommandType::Error;
  return comm_type;
}

std::unique_ptr<Operation> Interpreter::interpret_single(
    std::stringstream &ss) {
  try {
    auto type = interpret_command_type(ss);
    if (type == CommandType::Error) return {};

    std::string tok;
    ss >> tok;
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
      default:
        BOOST_ASSERT_MSG(type != CommandType::Repeat,
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
    else if (c == ',')
      ss >> std::skipws;
    else
      return {};
  }
}
