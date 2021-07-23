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

#include <gtkmm.h>

#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>

#include "top.h"

namespace logging = boost::log;

int main(int argc, char *argv[]) {
#ifdef NDEBUG
  logging::core::get()->set_filter(logging::trivial::severity >=
                                   logging::trivial::info);
#else
  logging::core::get()->set_filter(logging::trivial::severity >=
                                   logging::trivial::trace);
#endif

  auto app = Gtk::Application::create(argc, argv, "org.deep.logo");
  LogoWindow window;
  window.maximize();
  return app->run(window);
}
