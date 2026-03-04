cmake_minimum_required(VERSION 3.16)

project(Practica4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Practica4 main.cpp
    auxiliares.h auxiliares.cpp
    README.md
    .gitignore
    codificar.h codificar.cpp)

include(GNUInstallDirs)
install(TARGETS Practica4
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
