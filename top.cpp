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

#include "top.h"

#include <boost/log/trivial.hpp>
#include <cmath>
#include <utility>

LogoDrawingArea::LogoDrawingArea(std::shared_ptr<Turtle> turtle)
    : turtle{std::move(turtle)} {
  set_size_request(LogoWindow::WIDTH, LogoWindow::HEIGHT);
  set_vexpand(true);
}

bool LogoDrawingArea::on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
  auto allocation = get_allocation();
  int width = allocation.get_width();
  int height = allocation.get_height();

  cr->save();
  cr->set_line_width(2.0);
  cr->set_source_rgb(1, 0, 0);
  draw_turtle(cr, width, height);
  cr->stroke();
  cr->set_source_rgb(0, 0, 0);
  draw_lines(cr, width, height);
  cr->stroke();
  cr->restore();

  return true;
}

void LogoDrawingArea::draw_turtle(const Cairo::RefPtr<Cairo::Context> &cr,
                                  int width, int height) const {
  int cx = width / 2;
  int cy = height / 2;

  double base_x = cx + turtle->get_x();
  double base_y = cy + turtle->get_y();

  double theta = static_cast<double>(turtle->get_angle()) * M_PI / 180.0;
  double theta_left = theta - M_PI_2;
  double theta_right = theta + M_PI_2;

  double x_left =
      base_x + LogoDrawingArea::TRIANGLE_WIDTH / 2.0 * sin(theta_left);
  double y_left =
      base_y - LogoDrawingArea::TRIANGLE_WIDTH / 2.0 * cos(theta_left);

  double x_right =
      base_x + LogoDrawingArea::TRIANGLE_WIDTH / 2.0 * sin(theta_right);
  double y_right =
      base_y - LogoDrawingArea::TRIANGLE_WIDTH / 2.0 * cos(theta_right);

  double x_top = base_x + LogoDrawingArea::TRIANGLE_HEIGHT * sin(theta);
  double y_top = base_y - LogoDrawingArea::TRIANGLE_HEIGHT * cos(theta);

  cr->move_to(base_x, base_y);
  cr->line_to(x_left, y_left);
  cr->line_to(x_top, y_top);
  cr->line_to(x_right, y_right);
  cr->line_to(base_x, base_y);
}

void LogoDrawingArea::draw_lines(const Cairo::RefPtr<Cairo::Context> &cr,
                                 int width, int height) const {
  int cx = width / 2;
  int cy = height / 2;

  for (const auto &line : lines) {
    const auto &start = line.start;
    const auto &end = line.end;
    cr->move_to(cx + start.x, cy + start.y);
    cr->line_to(cx + end.x, cy + end.y);
  }
}

LogoWindow::LogoWindow()
    : run_button("Run"), turtle{std::make_shared<Turtle>()}, area{turtle} {
  set_title("LOGO");
  auto vbox = Gtk::make_managed<Gtk::VBox>();
  auto hbox = Gtk::make_managed<Gtk::HBox>();
  auto area_frame = Gtk::make_managed<Gtk::Frame>();

  this->add(*vbox);

  area_frame->set_margin_top(20);
  area_frame->set_margin_bottom(20);
  area_frame->set_margin_right(20);
  area_frame->set_margin_left(20);
  area_frame->set_shadow_type(Gtk::SHADOW_ETCHED_IN);

  cmd_entry.set_margin_end(15);
  cmd_entry.set_margin_bottom(20);
  cmd_entry.set_margin_start(20);
  cmd_entry.signal_activate().connect(
      sigc::mem_fun(*this, &LogoWindow::on_run));
  cmd_entry.signal_changed().connect(
      sigc::mem_fun(*this, &LogoWindow::on_entry_changed));
  auto prompt_icon =
      Gdk::Pixbuf::create_from_resource("/window/assets/prompt-arrow.svg");
  cmd_entry.set_icon_from_pixbuf(prompt_icon);

  run_button.set_margin_start(15);
  run_button.set_margin_bottom(20);
  run_button.set_margin_end(20);
  run_button.signal_clicked().connect(
      sigc::mem_fun(*this, &LogoWindow::on_run));

  err_label.set_margin_bottom(20);
  err_label.set_margin_left(20);
  err_label.set_alignment(0);

  area_frame->add(area);
  vbox->pack_start(*area_frame);
  area.show();
  area_frame->show();
  vbox->pack_start(*hbox, Gtk::PACK_SHRINK);
  hbox->pack_start(cmd_entry);
  cmd_entry.show();
  hbox->pack_start(run_button, Gtk::PACK_SHRINK);
  run_button.show();
  hbox->show();
  vbox->pack_start(err_label, Gtk::PACK_SHRINK);
  err_label.show();
  vbox->show();
  show();
}

void LogoWindow::perform_operation(Operation &op) {
  if (const auto *rep = dynamic_cast<RepeatOperation *>(&op)) {
    for (int i = 0, cnt = rep->get_cnt(); i < cnt; ++i)
      for (const auto &sub_op : rep->get_ops()) perform_operation(*sub_op);
  } else if (const auto *cls = dynamic_cast<ClearScreenOperation *>(&op)) {
    cls->action(*turtle);
    area.clear();
  } else {
    auto old_pos = turtle->get_position();
    op.action(*turtle);
    auto new_pos = turtle->get_position();
    if (old_pos != new_pos) {
      BOOST_LOG_TRIVIAL(debug)
          << "Position changed from " << old_pos << " to " << new_pos;
      if (turtle->is_pen_down()) {
        BOOST_LOG_TRIVIAL(debug) << "Drawing line";
        area.add_line({old_pos, new_pos});
      }
    }
  }
  area.queue_draw();
}

void LogoWindow::on_run() {
  const auto &comm = cmd_entry.get_text();
  const auto op = Interpreter::interpret(comm);
  if (op) {
    BOOST_LOG_TRIVIAL(debug) << *op;
    perform_operation(*op);
    cmd_entry.set_text("");
    err_label.set_text("");
  } else {
    BOOST_LOG_TRIVIAL(info)
        << "failed to interpret command: \"" << comm << "\"";
    err_label.set_markup(
        "<span foreground='red' weight='bold' font='12'>Invalid "
        "command</span>");
  }
}

void LogoWindow::on_entry_changed() {
  auto text = cmd_entry.get_text();
  cmd_entry.set_text(text.uppercase());
}
