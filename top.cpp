#include "top.h"
#include <cmath>

LogoDrawingArea::LogoDrawingArea(const std::shared_ptr<Turtle> &turtle)
    : turtle{turtle} {
  set_draw_func(sigc::mem_fun(*this, &LogoDrawingArea::on_draw));
  set_size_request(LogoWindow::WIDTH, LogoWindow::HEIGHT);
}

void LogoDrawingArea::on_draw(const Cairo::RefPtr<Cairo::Context> &cr,
                              int width, int height) const {
  cr->set_line_width(2.5);
  draw_turtle(cr, width, height);
  cr->stroke();
}

void LogoDrawingArea::draw_turtle(const Cairo::RefPtr<Cairo::Context> &cr,
                                  int width, int height) const {
  int cx = width / 2;
  int cy = width / 2;

  int base_x = cx + turtle->get_x();
  int base_y = cy + turtle->get_y();
  
  double theta = turtle->get_angle() * M_PI / 180.0;
  double theta_left = theta - M_PI_2;
  double theta_right = theta + M_PI_2;

  double x_left = base_x - LogoDrawingArea::TRIANGLE_WIDTH / 2.0 * cos(theta_left);
  double y_left = base_y + LogoDrawingArea::TRIANGLE_WIDTH / 2.0 * sin(theta_left);

  double x_right = base_x - LogoDrawingArea::TRIANGLE_WIDTH / 2.0 * cos(theta_right);
  double y_right = base_y + LogoDrawingArea::TRIANGLE_WIDTH / 2.0 * sin(theta_right);

  double x_top = base_x - LogoDrawingArea::TRIANGLE_HEIGHT * cos(theta);
  double y_top = base_y + LogoDrawingArea::TRIANGLE_HEIGHT * sin(theta);

  cr->move_to(base_y, base_x);
  cr->line_to(y_left, x_left);
  cr->line_to(y_top, x_top);
  cr->line_to(y_right, x_right);
  cr->line_to(base_y, base_x);
}

LogoWindow::LogoWindow()
    : vbox(Gtk::Orientation::VERTICAL), hbox(Gtk::Orientation::HORIZONTAL),
      run_button("Run"), turtle{std::make_shared<Turtle>()}, area{turtle} {
  set_title("LOGO");
  set_child(vbox);

  cmd_entry.set_expand(true);
  cmd_entry.set_margin_end(15);
  cmd_entry.set_margin_bottom(20);
  cmd_entry.set_margin_start(20);

  run_button.set_margin_start(15);
  run_button.set_margin_bottom(20);
  run_button.set_margin_end(20);

  vbox.append(area);
  vbox.append(hbox);
  hbox.append(cmd_entry);
  hbox.append(run_button);
}
