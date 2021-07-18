#ifndef __TOP_H__
#define __TOP_H__

#include <gtkmm.h>

#include <memory>
#include <vector>

#include "interpreter.h"
#include "turtle.h"

class LogoDrawingArea : public Gtk::DrawingArea {
 public:
  LogoDrawingArea(const std::shared_ptr<Turtle> &turtle);
  virtual ~LogoDrawingArea() {}
  void add_line(const Line &line) { lines.push_back(line); }

  constexpr static int TRIANGLE_HEIGHT = 10;  // px
  constexpr static int TRIANGLE_WIDTH = 8;    // px

 private:
  void on_draw(const Cairo::RefPtr<Cairo::Context> &cr, int width,
               int height) const;
  void draw_turtle(const Cairo::RefPtr<Cairo::Context> &cr, int width,
                   int height) const;
  void draw_lines(const Cairo::RefPtr<Cairo::Context> &cr, int width,
                  int height) const;

  std::shared_ptr<Turtle> turtle;
  std::vector<Line> lines;
};

class LogoWindow : public Gtk::Window {
 public:
  LogoWindow();

  constexpr static int WIDTH = 500;
  constexpr static int HEIGHT = 500;

 private:
  void perform_operation(Operation &op);
  void on_run();

  Gtk::Box vbox;
  Gtk::Box hbox;
  Gtk::Button run_button;
  Gtk::Entry cmd_entry;
  std::shared_ptr<Turtle> turtle;
  LogoDrawingArea area;
  Interpreter interpreter;
};

#endif  // __TOP_H__
