#include "top.h"

#include <boost/log/trivial.hpp>
#include <cmath>
#include <utility>

LogoDrawingArea::LogoDrawingArea(std::shared_ptr<Turtle> turtle)
    : turtle{std::move(turtle)} {
  set_draw_func(sigc::mem_fun(*this, &LogoDrawingArea::on_draw));
  set_size_request(LogoWindow::WIDTH, LogoWindow::HEIGHT);
  set_vexpand(true);
}

void LogoDrawingArea::on_draw(const Cairo::RefPtr<Cairo::Context> &cr,
                              int width, int height) const {
  cr->save();
  cr->set_line_width(2.0);
  cr->set_source_rgb(1, 0, 0);
  draw_turtle(cr, width, height);
  cr->stroke();
  cr->set_source_rgb(0, 0, 0);
  draw_lines(cr, width, height);
  cr->stroke();
  cr->restore();
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
    : vbox(Gtk::Orientation::VERTICAL),
      hbox(Gtk::Orientation::HORIZONTAL),
      run_button("Run"),
      turtle{std::make_shared<Turtle>()},
      area{turtle} {
  set_title("LOGO");
  set_child(vbox);

  cmd_entry.set_hexpand(true);
  cmd_entry.set_margin_end(15);
  cmd_entry.set_margin_bottom(20);
  cmd_entry.set_margin_start(20);

  run_button.set_margin_start(15);
  run_button.set_margin_bottom(20);
  run_button.set_margin_end(20);
  run_button.signal_clicked().connect(
      sigc::mem_fun(*this, &LogoWindow::on_run));

  vbox.append(area);
  vbox.append(hbox);
  hbox.append(cmd_entry);
  hbox.append(run_button);
}

void LogoWindow::perform_operation(Operation &op) {
  if (const auto *rep = dynamic_cast<RepeatOperation *>(&op)) {
    for (int i = 0, cnt = rep->get_cnt(); i < cnt; ++i)
      for (const auto &sub_op : rep->get_ops()) perform_operation(*sub_op);
  } else {
    auto old_pos = turtle->get_position();
    op.action(*turtle);
    auto new_pos = turtle->get_position();
    if (old_pos != new_pos) {
      BOOST_LOG_TRIVIAL(debug)
          << "Position changed from " << old_pos << " to " << new_pos;
      area.add_line({old_pos, new_pos});
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
  } else {
    BOOST_LOG_TRIVIAL(info)
        << "failed to interpret command: \"" << comm << "\"";
  }
}
