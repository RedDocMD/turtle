#include "interpreter.h"
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/log/trivial.hpp>
#include <vector>

std::optional<std::unique_ptr<Operation>>
Interpreter::interpret(const std::string &command) {
  auto comm = command;
  boost::trim(comm);

  try {
    std::smatch match;
    if (std::regex_search(comm, match, fd_reg)) {
      int amt = boost::lexical_cast<int>(match[1]);
      return std::make_unique<ForwardOperation>(amt);
    } else if (std::regex_search(comm, match, bk_reg)) {
      int amt = boost::lexical_cast<int>(match[1]);
      return std::make_unique<BackwardOperation>(amt);
    } else if (std::regex_search(comm, match, rt_reg)) {
      int amt = boost::lexical_cast<int>(match[1]);
      return std::make_unique<RightTurnOperation>(amt);
    } else if (std::regex_search(comm, match, lt_reg)) {
      int amt = boost::lexical_cast<int>(match[1]);
      return std::make_unique<LeftTurnOperation>(amt);
    } else if (std::regex_search(comm, match, rep_reg)) {
      int cnt = boost::lexical_cast<int>(match[1]);
      std::vector<std::string> part_comms;
      std::string rep_comm = match[2];
      // FIXME: This can't handle anything more than simple repeats
      boost::split(part_comms, rep_comm, boost::is_any_of(","));
      std::vector<std::optional<std::unique_ptr<Operation>>> comms(
          part_comms.size());
      std::transform(
          part_comms.begin(), part_comms.end(),
          comms.begin(), [&](const auto &str) -> auto {
            return this->interpret(str);
          });
      if (std::all_of(
              comms.begin(), comms.end(),
              [](const auto &comm) -> auto { return comm.has_value(); })) {
        std::vector<std::unique_ptr<Operation>> ops;
        ops.reserve(comm.size());
        for (auto &comm_opt : comms)
          ops.push_back(std::move(*comm_opt));
        return std::make_unique<RepeatOperation>(cnt, std::move(ops));
      } else {
        return {};
      }
    }
  } catch (const boost::bad_lexical_cast &) {
    BOOST_LOG_TRIVIAL(debug) << "bad number";
  }
  return {};
}
