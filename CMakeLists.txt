# cmake_minimum_required(VERSION <specify CMake version here>)
project(JeuTuto)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(JeuTuto
        bullet.cpp
        bullet.h
        main.cpp
        mainwindow.cpp
        mainwindow.h
        MyRect.cpp
        MyRect.h
        view.cpp
        view.h)
