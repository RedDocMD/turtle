cmake_minimum_required(VERSION 3.10)
project(Turtle VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)
find_package(Boost COMPONENTS log REQUIRED)

# Compile the resources
find_program(GLIB_COMPILE_RESOURCES NAMES glib-compile-resources REQUIRED)

set(GRESOURCE_C turtle_gresource.c)
set(GRESOURCE_XML turtle.gresource.xml)

add_custom_command(
        OUTPUT ${GRESOURCE_C}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND ${GLIB_COMPILE_RESOURCES}
        ARGS
            --target=${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C}
            --generate-source
            ${GRESOURCE_XML}
        VERBATIM
        MAIN_DEPENDENCY ${GRESOURCE_XML}
        DEPENDS
            assets/logo.svg
)
add_custom_target(
        resources
        DEPENDS
            ${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C}
)


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
add_executable(turtle ${SOURCES} main.cpp ${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C})
set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C} PROPERTIES GENERATED TRUE)
add_dependencies(turtle resources)
target_compile_options(turtle PRIVATE -Wall -pedantic)
target_link_libraries(turtle PRIVATE ${GTKMM_LIBRARIES} ${Boost_LIBRARIES})
target_include_directories(turtle PRIVATE ${GTKMM_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
