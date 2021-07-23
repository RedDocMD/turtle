set(SOURCES
        geom.cpp
        interpreter.cpp
        top.cpp
        turtle.cpp
)
add_library(libturtle SHARED ${SOURCES})
target_compile_options(libturtle PRIVATE -Wall -pedantic)
target_include_directories(libturtle PUBLIC ../include ${GTKMM_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
target_link_libraries(libturtle PUBLIC ${GTKMM_LIBRARIES} ${Boost_LIBRARIES})