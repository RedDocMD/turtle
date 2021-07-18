cmake_minimum_required(VERSION 3.10)
project(Turtle VERSION 0.1.0)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)
find_package(Boost COMPONENTS log REQUIRED)

set(SOURCES
        top.cpp
        top.h
        turtle.cpp
        turtle.h
        geom.h
        geom.cpp
        interpreter.h
        interpreter.cpp
        )
add_executable(turtle ${SOURCES} main.cpp)
target_compile_options(turtle PRIVATE -Wall -pedantic -std=c++17)
target_link_libraries(turtle PRIVATE ${GTKMM_LIBRARIES} ${Boost_LIBRARIES})
target_include_directories(turtle PRIVATE ${GTKMM_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
