#ifndef __TOP_H__
#define __TOP_H__

#include <gtkmm.h>

class LogoDrawingArea : public Gtk::DrawingArea {
public:
  LogoDrawingArea();
  virtual ~LogoDrawingArea() {}

private:
  void on_draw(const Cairo::RefPtr<Cairo::Context> &cr, int width, int height);
};

class LogoWindow : public Gtk::Window {
public:
  LogoWindow();

  constexpr static int WIDTH = 500;
  constexpr static int HEIGHT = 500;
private:
  LogoDrawingArea area;
  Gtk::Box vbox;
  Gtk::Box hbox;
  Gtk::Button run_button;
  Gtk::Entry cmd_entry;
};

#endif // __TOP_H__
