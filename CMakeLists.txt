cmake_minimum_required(VERSION 3.22)
project(Computer_Architecture)

set(CMAKE_CXX_STANDARD 17)

add_executable(Project1 Project1/main.c
        Project1/instruction_cycle.c)

add_executable(Project2 Project2/main.c
        Project2/component/register.h
        Project2/component/register_impl.c)