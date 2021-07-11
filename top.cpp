#include "top.h"

LogoDrawingArea::LogoDrawingArea() {
  set_draw_func(sigc::mem_fun(*this, &LogoDrawingArea::on_draw));
  set_size_request(LogoWindow::WIDTH, LogoWindow::HEIGHT);
}

void LogoDrawingArea::on_draw(const Cairo::RefPtr<Cairo::Context> &cr,
                              int width, int height) {}

LogoWindow::LogoWindow()
    : vbox(Gtk::Orientation::VERTICAL), hbox(Gtk::Orientation::HORIZONTAL),
      run_button("Run") {
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
