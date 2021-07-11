#ifndef __TOP_H__
#define __TOP_H__

#include "turtle.h"
#include <gtkmm.h>
#include <memory>

class LogoDrawingArea : public Gtk::DrawingArea {
public:
  LogoDrawingArea(const std::shared_ptr<Turtle> &turtle);
  virtual ~LogoDrawingArea() {}

  // 1 unit of LOGO corresponds to SCALE_FACTOR px
  constexpr static int SCALE_FACTOR = 5;

  constexpr static int TRIANGLE_HEIGHT = 10; // px
  constexpr static int TRIANGLE_WIDTH = 10; // px

private:
  void on_draw(const Cairo::RefPtr<Cairo::Context> &cr, int width, int height) const;
  void draw_turtle(const Cairo::RefPtr<Cairo::Context> &cr, int width, int height) const;

  std::shared_ptr<Turtle> turtle;
};

class LogoWindow : public Gtk::Window {
public:
  LogoWindow();

  constexpr static int WIDTH = 500;
  constexpr static int HEIGHT = 500;

private:
  Gtk::Box vbox;
  Gtk::Box hbox;
  Gtk::Button run_button;
  Gtk::Entry cmd_entry;
  std::shared_ptr<Turtle> turtle;
  LogoDrawingArea area;
};

#endif // __TOP_H__
