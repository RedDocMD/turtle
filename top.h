#ifndef __TOP_H__
#define __TOP_H__

#include <gtkmm.h>

#include <memory>
#include <vector>

#include "interpreter.h"
#include "turtle.h"

class LogoDrawingArea : public Gtk::DrawingArea {
 public:
  explicit LogoDrawingArea(std::shared_ptr<Turtle> turtle);
  ~LogoDrawingArea() override = default;
  void add_line(const Line &line) { lines.push_back(line); }

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

class LogoWindow : public Gtk::Window {
 public:
  LogoWindow();

  constexpr static int WIDTH = 500;
  constexpr static int HEIGHT = 500;

 private:
  void perform_operation(Operation &op);
  void on_run();

  Gtk::VBox vbox;
  Gtk::HBox hbox;
  Gtk::Button run_button;
  Gtk::Entry cmd_entry;
  std::shared_ptr<Turtle> turtle;
  LogoDrawingArea area;
};

#endif  // __TOP_H__
