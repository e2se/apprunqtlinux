cmake_minimum_required(VERSION 3.22)
project(AppRun)

set(CMAKE_C_STANDARD 11)

add_executable(AppRun main.c)

install(TARGETS AppRun)

