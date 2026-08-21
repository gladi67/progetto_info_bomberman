cmake_minimum_required(VERSION 4.1)
project(Bomberman)

set(CMAKE_CXX_STANDARD 20)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(Bomberman
        main.cpp
        Menu.cpp
        Menu.hpp
        Tempo.cpp
        Tempo.hpp
        Punti.cpp
        Punti.hpp
        fine.cpp
        fine.hpp
        Classifica.cpp
        Classifica.hpp
        Gamemaster.cpp
        Gamemaster.hpp
        Schermo.cpp
        Schermo.hpp
)

target_link_libraries(Bomberman ${CURSES_LIBRARIES})
