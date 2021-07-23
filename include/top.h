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

#ifndef __TOP_H__
#define __TOP_H__

#include <gtkmm.h>

#include <algorithm>
#include <boost/log/trivial.hpp>
#include <memory>
#include <vector>

#include "interpreter.h"
#include "turtle.h"

class LogoDrawingArea : public Gtk::DrawingArea {
 public:
  explicit LogoDrawingArea(std::shared_ptr<Turtle> turtle);
  ~LogoDrawingArea() override = default;
  void add_line(const Line &line) { lines.push_back(line); }
  void clear() { lines.clear(); }

  constexpr static int TRIANGLE_HEIGHT = 10;  // px
  constexpr static int TRIANGLE_WIDTH = 8;    // px

 private:
  bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) override;
  void draw_turtle(const Cairo::RefPtr<Cairo::Context> &cr, int width,
                   int height) const;
  void draw_lines(const Cairo::RefPtr<Cairo::Context> &cr, int width,
                  int height) const;

  std::shared_ptr<Turtle> turtle;
  std::vector<Line> lines;
};

class CommandStack {
  std::vector<std::string> stack;
  size_t curr;

 public:
  CommandStack() : stack{""}, curr{0} {}
  ~CommandStack() = default;
  [[nodiscard]] const std::string &curr_command() const { return stack[curr]; }
  void move_up() {
    if (curr > 0) --curr;
  }
  void move_down() {
    if (curr < stack.size() - 1) ++curr;
  }
  void push() {
    if (curr != stack.size() - 1) {
      stack.pop_back();
      stack.push_back(stack[curr]);
    }
    stack.emplace_back("");
    curr = stack.size() - 1;
  }
  void update_curr(std::string new_comm) { stack[curr] = std::move(new_comm); }
  void dump() {
    std::string str = "[";
    for (auto i = 0UL; i < stack.size(); ++i) {
      if (i == curr) str += "{";
      str += "\"" + stack[i] + "\"";
      if (i == curr) str += "}";
      if (i != stack.size() - 1) str += ", ";
    }
    str += "]";
    BOOST_LOG_TRIVIAL(trace) << str;
  }
};

class LogoWindow : public Gtk::Window {
 public:
  LogoWindow();

  constexpr static int WIDTH = 500;
  constexpr static int HEIGHT = 500;

 private:
  void perform_operation(Operation &op);
  void on_run();
  void on_entry_changed();
  bool on_entry_key_release_event(GdkEventKey *key);

  Gtk::Button run_button;
  Gtk::Entry cmd_entry;
  Gtk::Label err_label;

  std::shared_ptr<Turtle> turtle;
  LogoDrawingArea area;
  CommandStack stack;
};

#endif  // __TOP_H__
