cmake_minimum_required(VERSION 3.10)
project(Turtle VERSION 0.1.0)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)

set(SOURCES
    top.cpp
    top.h
)
add_executable(turtle main.cpp ${SOURCES})
target_compile_options(turtle PRIVATE -Wall -Werror -pedantic -std=c++17)
target_link_libraries(turtle PRIVATE ${GTKMM_LIBRARIES})
target_include_directories(turtle PRIVATE ${GTKMM_INCLUDE_DIRS})
