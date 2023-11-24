cmake_minimum_required(VERSION 3.23.2)
project(projetS1 C)

set(CMAKE_C_STANDARD 23)

add_executable(projetS1 main.c
        initialisation.c
        Header_general.h
        Exclusions.h Exclusions.c
        Precedence.h
        Precedence.c)
